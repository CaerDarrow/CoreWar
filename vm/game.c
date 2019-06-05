/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:52:41 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/05 14:31:26 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			print_bg(t_game_entity *entity)
{
	int			i;
	i = -1;
	while (++i < MEM_SIZE)
	{
		ft_printf("%02x ", entity->bg[i]);
		if (i % 64 == 63)
			ft_printf("\n");
	}
}

int				is_valide_reg(int n)
{
	return (n > 0 && n <= 16);
}

void			set_reg_num(t_cursor *cursor, int n, int value)//only less or eq to u32
{
	int			i;

	i = -1;
	if (!is_valide_reg(n))
		error("Invalid register");
	while (++i < REG_SIZE)
		cursor->reg[n - 1][i] = (value >> (32 - 8 * (i + 1))) & 0xFF;
}

unsigned char	**get_reg_num(t_cursor *cursor, int n)//only less or eq to u32
{
	if (!is_valide_reg(n))
		error("Invalid register");
		ft_printf("getreg: %d\n", get_num(cursor->reg[n - 1]));
	return (&cursor->reg[n - 1]);
	// return ptr unsigned char*
}

int				time_to_apply_op(t_cursor *cursor)
{
	if (cursor->cycles_to_exec && !is_valide_op(cursor->op_code))///
		error("Unexpected error :: invalid op code");///
		// return (0);
	return (cursor->cycles_to_exec == 0);
}

int				is_valide_op(char op_code)
{
	return (op_code >= 0 && op_code <= 16);
}

int				is_live_op(char op_code)
{
	return (op_code == 1);
}

int				is_valide_type(unsigned char argc, int op_code)
{
	int					i;
	int					type;
	int					code;

	i = -1;
	while (++i < g_op_tab[op_code].argc)
	{
		type = g_op_tab[op_code].argv[i];
		code = (argc >> (6 - i * 2)) & 0b11;
		if (!(((type & T_DIR) && (code == DIR_CODE)) ||
			((type & T_IND) && (code == IND_CODE)) ||
			((type & T_REG) && (code == REG_CODE))))
			return (0);
	}
	return (1);
}

void			*get_op_by_code(unsigned char op_code)
{
	return (g_op_ptr[op_code]);
}

unsigned char	get_op_code(unsigned char *bg, int position)
{
	return (bg[position % IDX_MOD]);
}

unsigned char	read_args_type(unsigned char *bg, int position)
{
	return (bg[(position + 1) % IDX_MOD]);
}

unsigned char		get_dir_size(unsigned char op_code)
{
	if (g_op_tab[op_code].t_dirsize)
		return (DIR_SIZE);
	return (IND_SIZE);
}

unsigned char		*get_dir_value(unsigned char *bg, int position, int offset, int size)
{
	int				addr;
	unsigned char	*res;
	int				i;

	if (!(res = (unsigned char	*)ft_strnew(size)))
		error("Malloc error");
	addr = position + 1 + offset;
	if (addr < 0)
		addr += MEM_SIZE;
	addr %= IDX_MOD;
	i = -1;
	while (++i < size)
		res[i] = bg[addr + i];
	return (res);
}

unsigned char		**get_ind_value(unsigned char *bg, int position, int offset)
{
	int				addr;
	unsigned char	**res;
	int				i;

	res = 0;// trash
	// res = malloc(8);
	if (!(*res = (unsigned char	*)ft_strnew(IND_SIZE)))
		error("Malloc error");
	addr = position + 1 + offset;
	if (addr < 0)
		addr += MEM_SIZE;
	addr %= IDX_MOD;
	i = -1;
	while (++i < IND_SIZE)
		addr = (addr | (bg[addr + i] << ((IND_SIZE - i) * 2)));
	i = -1;
	while (++i < IND_SIZE)
		(*res)[i] = bg[addr + i];
	return (res);
}

unsigned char	*read_args(t_cursor *cursor, unsigned char *bg, unsigned char argc)
{
	unsigned char		*res;
	int					i;
	int					code;
	int					offset;

	(void)argc;
	(void)bg;
	res = 0;
	offset = 0;
	i = -1;
	ft_printf("argc:%d\n", g_op_tab[cursor->op_code].argc);
	while (++i < g_op_tab[cursor->op_code].argc)
	{
		code = (argc >> (6 - i * 2)) & 0b11;//get code ?
		if (code == DIR_CODE)
		{
			ft_printf("Read dir\n");
			res = (unsigned char *)ft_strmerge(2, (char **)&res, (char **)get_dir_value(bg, cursor->position, offset, get_dir_size(cursor->op_code)));
			offset += get_dir_size(cursor->op_code);
		}
		else if (code == IND_CODE)
		{
			ft_printf("Read ind\n");
			res = (unsigned char *)ft_strmerge(2, (char **)&res, (char **)get_ind_value(bg, cursor->position, offset));
			offset += IND_SIZE;
		}
		else if (code == REG_CODE)
		{
			ft_printf("Read reg\n");
			res = (unsigned char *)ft_strmerge(2, (char **)&res, (char **)get_reg_num(cursor, bg[cursor->position + 2 + offset]));
			ft_printf("read reg arg: %s\n", res);
			offset += 1;
		}
		else
			error("Unexpected: Wrong code");
	}
	return (res);
}

int						apply_op(t_game_entity *entity, t_cursor *cursor)
{
	unsigned char		argc;
	unsigned char		*argv;
	void				(*f)(t_game_entity *, t_cursor *,
						unsigned char, unsigned char *);

	argv = 0;///
	f = get_op_by_code(cursor->op_code);
	argc = DIR_CODE << 6;
	if (g_op_tab[cursor->op_code].argtypes)
		argc = read_args_type(entity->bg, cursor->position);
	cursor->moved = 1;
	if (!is_valide_type(argc, cursor->op_code))
	{
		error("Invalide argv type");
		move_cursor(cursor, 1);
		return (-1);
	}
	argv = read_args(cursor, entity->bg, argc);
	ft_printf("argv:%s\n", argv);
	f(entity, cursor, argc, argv);
	ft_memdel((void**)&argv);
	move_cursor(cursor, cursor->step);
	return (cursor->op_code);
}

void			kill_cursor(t_list **cur)
{
	t_list		*prev;
	t_list		*b;

	if (!*cur || !cur)
		error("Unexpected error :: kill_cursor()");
	ft_printf("Someone just died; left alive: %d\n", l_full_size(*cur));
	prev = (*cur)->prev;
	if (prev)
	{
		b = (*cur)->next;
		prev->next = b;
		destroy_cur(cur);
		*cur = prev;
		if (b)
		{
			*cur = b;
			(*cur)->prev = prev;
		}
	}
	else
	{
		b = (*cur)->next;
		destroy_cur(cur);
		*cur = b;
		if (*cur)
			(*cur)->prev = 0;
	}
}

void			try_kill_cursors(t_game_entity *entity)
{
	t_list		*cursor;
	t_list		*prev;

	prev = 0;
	cursor = entity->cursors;
	while (cursor)
	{
		if (cursor_should_die(cursor, entity->cycles_to_die))
		{
			if (prev)
			{
				ft_printf("Died at %d\n", entity->cycles_to_die );
				kill_cursor(&cursor);
			}
			else
			{
				ft_printf("Died at %d\n", entity->cycles_to_die );

				kill_cursor(&entity->cursors);
				cursor = entity->cursors;
				continue;
			}
		}
		prev = cursor;
		cursor = cursor ? cursor->next : 0;
	}
	if (entity->cursors && entity->cursors->prev)
		error("Unexpected error :: lose cursor");
}

void			check_cursors(t_game_entity *entity, int *live_calls)
{
	if (entity->cycle % entity->cycles_to_die == 0 ||
		entity->cycles_to_die <= 0)
	{
		try_kill_cursors(entity);
		if (*live_calls >= NBR_LIVE ||
			entity->cycles_with_same_ctd == MAX_CHECKS)
		{
			entity->cycles_to_die -= CYCLE_DELTA;
			entity->cycles_with_same_ctd = 0;
		}
		else
			entity->cycles_with_same_ctd++;
		*live_calls = 0;
	}
}

int				get_exec_time_by_code(unsigned char op_code)
{
	return (g_op_tab[op_code].cycles);
}

void			set_op_code(t_cursor *cursor, unsigned char *bg)
{
	cursor->moved = 0;
	cursor->op_code = get_op_code(bg ,cursor->position);
	if (is_valide_op(cursor->op_code))
		cursor->cycles_to_exec = get_exec_time_by_code(cursor->op_code);
}

void			game_loop(t_game_entity *entity)
{
	(void)entity;
	t_list		*cursor_ptr;
	t_cursor	*cursor;
	int			live_calls;

	live_calls = 0;//hide in entity
	while (entity->cursors)
	{
		if (entity->cycle == 1534)
			ft_printf("BREAK\n");
		cursor_ptr = entity->cursors;
		while (cursor_ptr)
		{
			cursor = (t_cursor *)cursor_ptr->data;
			// ft_printf("%d\n\n", get_op_code(entity->bg ,cursor->position));
			// if else or if if ???
			if (cursor->moved)
				set_op_code(cursor, entity->bg);
			if (cursor->cycles_to_exec > 0)
				cursor->cycles_to_exec--;
			else if (cursor->cycles_to_exec == 0)
				if (is_live_op(apply_op(entity, cursor)))
					live_calls++;
			cursor_ptr = cursor_ptr->next;
		}
		entity->cycle++;
		// ft_printf("%d\n", entity->cycle);
		check_cursors(entity, &live_calls);
		// ft_printf("%d\n", live_calls);
	}
	print_bg(entity);
	//Choose winner
	ft_printf("\nGame end at %d, last alive player %d\n", entity->cycle , entity->last_alive_player);
}
