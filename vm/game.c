/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:52:41 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/31 16:25:03 by ajon-hol         ###   ########.fr       */
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

void			set_reg_num(t_cursor *c, int n, int value)//only less or eq to u32
{
	(void)c;(void)n;(void)value;
}

int				get_reg_num(t_cursor *c, int n)//only less or eq to u32
{
	(void)c;(void)n;
	return (n);
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

int				is_valide_type(unsigned char argc, unsigned char *argv)
{
	(void)argv;(void)argc;
	return (1);
}

void			*get_op_by_code(unsigned char op_code)
{
	return (g_op_ptr[op_code]);
}

unsigned char	get_op_code(unsigned char *bg, int position)
{
	return (bg[position]);
}

unsigned char	read_args_type(unsigned char *bg, int position)
{
	// &bg?
	(void)bg;(void)position;
	return (1);
}

unsigned char	*read_args(unsigned char *bg, int position)
{
	(void)bg;(void)position;
	return (0);
}

int						apply_op(t_game_entity *entity, t_cursor *cursor)
{
	unsigned char		argc;
	unsigned char		*argv;
	void				(*f)(t_game_entity *, t_cursor *,
						unsigned char, unsigned char *);

	f = get_op_by_code(cursor->op_code);
	argc = 0;
	if (g_op_tab[cursor->op_code].argtypes)
		argc = read_args_type(entity->bg, cursor->position);
	argv = read_args(entity->bg, cursor->position);
	cursor->moved = 1;
	if (!is_valide_type(argc, argv))
	{
		move_cursor(cursor, 1);
		return (-1);
	}
	f(entity, cursor, argc, argv);
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
	// print_bg(entity);
	//Choose winner
	ft_printf("\nGame end at %d, last alive player %d\n", entity->cycle - 1, entity->last_alive_player);
}
