/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:37:11 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/04 22:23:30 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

static void			apply_op_debug(t_uchar *bg, int position, int step)
{
	if (VERBOSE_LVL(16))
	{
		ft_printf("ADV %d (0x%04x -> 0x%04x) ",
			step,
			position,
			position + step);
		print_n_cells_after(bg, position, step);
	}
}

static int			skip_invalid_token(t_uchar *bg, t_cursor *cursor, int step,
						char debug)
{
	if (debug == DEBUG_ON)
		apply_op_debug(bg, cursor->position, step);
	move_cursor(cursor, step);
	return (-1);
}

int					apply_op(t_game_entity *entity, t_cursor *cursor)
{
	t_uchar			argc;
	t_list			*argv;
	int				step;
	void			(*f)(t_game_entity *, t_cursor *, t_uchar, t_list *);

	if (!(f = get_op_by_code(cursor->op_code)))
		return (skip_invalid_token(entity->bg, cursor, 1, DEBUG_OFF));
	if (!is_valid_argc((argc = get_argc(entity->bg, cursor)), cursor->op_code))
	{
		return (skip_invalid_token(entity->bg, cursor,
			1 + g_op_tab[cursor->op_code].argtypes, DEBUG_ON));
	}
	step = get_step(cursor->op_code, argc);
	if (!is_proper_argc(argc, cursor->op_code) ||
		!(argv = read_args(cursor, entity->bg, argc)))
		return (skip_invalid_token(entity->bg, cursor, step, DEBUG_ON));
	f(entity, cursor, argc, argv);
	l_destroy(&argv);
	if ((f == zjmp && !cursor->carry) || (f != zjmp))
	{
		apply_op_debug(entity->bg, cursor->position, step);
		move_cursor(cursor, step);
	}
	return (cursor->op_code);
}
