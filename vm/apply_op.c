/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:37:11 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/04 21:37:42 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			get_step(t_uchar op_code, t_uchar argc)
{
	int				i;
	int				res;
	int				flag;

	res = 1 + g_op_tab[op_code].argtypes;
	flag = g_op_tab[op_code].dir;
	i = -1;
	while (++i < g_op_tab[op_code].argc)
		res += get_arg_size(argc, flag, i + 1);
	return (res);
}

static void			*get_op_by_code(t_uchar op_code)
{
	if (!is_valid_op(op_code))
		return (NULL);
	return (g_op_tab[op_code].op);
}

static t_uchar		get_argc(t_uchar *bg, t_cursor *cursor)
{
	if (g_op_tab[cursor->op_code].argtypes)
		return (bg[correct_position(cursor->position + 1)]);
	return (DIR_CODE << 6);
}

static t_list		*read_args(t_cursor *cursor, t_uchar *bg, t_uchar argc)
{
	int				i;
	int				code;
	int				offset;
	t_list			*res;

	offset = g_op_tab[cursor->op_code].argtypes ? 2 : 1;
	i = 0;
	res = 0;
	while (++i <= g_op_tab[cursor->op_code].argc)
	{
		code = arg_code(argc, i);
		if (code == DIR_CODE)
			read_dir_value(&res, bg, cursor, &offset);
		else if (code == IND_CODE)
			read_ind_value(&res, bg, cursor, &offset);
		else if (code == REG_CODE)
			if (!read_reg_value(&res, bg, cursor, &offset))
				return (NULL);
	}
	return (res);
}

void			print_n_cells_after(t_uchar *bg, int position, int bytes)
{
	int			i;

	i = -1;
	while (++i < bytes)
	{
		ft_printf("%.2x ", bg[correct_position(position + i)]);
	}
	write(1, "\n", 1);
}

int					apply_op(t_game_entity *entity, t_cursor *cursor)
{
	t_uchar			argc;
	t_list			*argv;
	int				step;
	void			(*f)(t_game_entity *, t_cursor *, t_uchar, t_list *);

	if (!(f = get_op_by_code(cursor->op_code)))
	{
		move_cursor(cursor, 1);
		return (-1);
	}
	argc = get_argc(entity->bg, cursor);
	////////////
//// correct position can be added but carefully

	//////////
	if (!is_valid_argc(argc, cursor->op_code))
	{
		//ft_printf("STEP: %d |", step);
		step = 1 + g_op_tab[cursor->op_code].argtypes;
		if (VERBOSE_LVL(16))
		{
			ft_printf("ADV %d (0x%04x -> 0x%04x) ", step,
				cursor->position,
				(cursor->position + step));
			print_n_cells_after(entity->bg, cursor->position, step);
		}
		move_cursor(cursor, step);
		return (-1);
	}
	step = get_step(cursor->op_code, argc);

	if (!is_proper_argc(argc, cursor->op_code))
	{
		if (VERBOSE_LVL(16))
		{
			ft_printf("ADV %d (0x%04x -> 0x%04x) ", step,
				cursor->position,
				(cursor->position + step));
			print_n_cells_after(entity->bg, cursor->position, step);
		}
		move_cursor(cursor, step);
		return (-1);
	}

	if (!(argv = read_args(cursor, entity->bg, argc)))
	{
		if (VERBOSE_LVL(16))
		{
			ft_printf("ADV %d (0x%04x -> 0x%04x) ", step,
				cursor->position,
				(cursor->position + step));
			print_n_cells_after(entity->bg, cursor->position, step);
		}
		move_cursor(cursor, step);
		return (-1);
	}
	f(entity, cursor, argc, argv);
	l_destroy(&argv);
	if ((f == zjmp && !cursor->carry) || (f != zjmp))
	{
		if (VERBOSE_LVL(16))
		{
			ft_printf("ADV %d (0x%04x -> 0x%04x) ", step,
				cursor->position,
				(cursor->position + step));
			print_n_cells_after(entity->bg, cursor->position, step);
		}
		move_cursor(cursor, step);
	}
	return (cursor->op_code);
}
