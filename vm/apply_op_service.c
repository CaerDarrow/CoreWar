/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_op_service.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 22:19:33 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/05 19:02:43 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int					get_step(t_uchar op_code, t_uchar argc)
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

void				*get_op_by_code(t_uchar op_code)
{
	if (!is_valid_op(op_code))
		return (NULL);
	return (g_op_tab[op_code].op);
}

t_uchar				get_argc(t_uchar *bg, t_cursor *cursor)
{
	if (g_op_tab[cursor->op_code].argtypes)
		return (bg[correct_position(cursor->position + 1)]);
	return (DIR_CODE << 6);
}
