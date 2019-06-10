/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:37:11 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/10 14:05:48 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			get_step(t_uchar op_code, t_uchar argc, char flag)
{
	int				i;
	int				res;

	res = 1 + g_op_tab[op_code].argtypes;
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

	argv = 0;
	if (!(f = get_op_by_code(cursor->op_code)))
	{
		move_cursor(cursor, 1);
		return (1);
	}
	argc = DIR_CODE << 6;
	if (g_op_tab[cursor->op_code].argtypes)
		argc = read_args_type(entity->bg, cursor->position);
	cursor->moved = 1;
	if (!is_valid_type(argc, cursor->op_code))
	{
		error("Invalid argv type");////////////////tmp
		move_cursor(cursor, 1);
		return (-1);
	}
	argv = read_args(cursor, entity->bg, argc);
	f(entity, cursor, argc, argv);
	if (g_verbose)
		ft_printf("Exec: %s at %d by %d player's cursor; cycles to die: %d; live calls: %d\n", g_op_tab[cursor->op_code].name, entity->cycle, cursor->id, entity->cycles_to_die, entity->live_calls);
	l_destroy(&argv);
	if (f != zjmp)
		move_cursor(cursor, get_step(cursor->op_code, argc, g_op_tab[cursor->op_code].t_dirsize));
	return (cursor->op_code);
}
