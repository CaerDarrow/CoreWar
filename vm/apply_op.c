/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:37:11 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/26 14:22:20 by jjacobso         ###   ########.fr       */
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

static t_uchar			read_args_type(t_uchar *bg, int position)
{
	return (bg[correct_position(position + 1)]);
}

static void				*get_op_by_code(t_uchar op_code)
{
	if (!is_valid_op(op_code))
		return (NULL);
	return (g_op_tab[op_code].op);
}
int						time_to_apply_op(t_cursor *cursor)
{
	if (cursor->cycles_to_exec && !is_valid_op(cursor->op_code))///
		error("Unexpected error :: invalid op code");///
		// return (0);
	return (cursor->cycles_to_exec == 0);
}

int						apply_op(t_game_entity *entity, t_cursor *cursor)
{
	t_uchar				argc;
	t_list				*argv;
	void				(*f)(t_game_entity *, t_cursor *,
						t_uchar, t_list *);
	char				carry;

	carry = cursor->carry;
	argv = 0;


	if (!(f = get_op_by_code(cursor->op_code)))
	{
		move_cursor(cursor, 1);
		return (-1);
	}
	argc = DIR_CODE << 6;
	if (g_op_tab[cursor->op_code].argtypes)
		argc = read_args_type(entity->bg, cursor->position);
	if (!is_valid_argc(argc, cursor->op_code))
	{
		// error("Invalid argv type");////////////////tmp
		move_cursor(cursor, 1);
		return (-1);
	}
	else if (!is_proper_argc(argc, cursor->op_code))
	{
		// error("Invalid argv type");////////////////tmp
		move_cursor(cursor, get_step(cursor->op_code, argc));
		return (-1);
	}
	if (!(argv = read_args(cursor, entity->bg, argc)))
	{
		move_cursor(cursor, get_step(cursor->op_code, argc));
		return (-1);
	}
	f(entity, cursor, argc, argv);
	l_destroy(&argv);
	if ((f == zjmp && !carry) || (f != zjmp))
		move_cursor(cursor, get_step(cursor->op_code, argc));
	return (cursor->op_code);
}
