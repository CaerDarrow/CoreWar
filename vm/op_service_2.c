/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_service_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 18:26:17 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/04 19:15:34 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int					get_rawarg(t_list *argv, int argc, int n, int flag)
{
	if (get_arg_size(argc, flag, n) == 2)
		return (*(short *)l_get_data(&argv, n));
	return (*(int *)l_get_data(&argv, n));
}

int					get_num_by_addr(unsigned char *bg, int addr, int size)
{
	int				i;
	int				res;

	res = 0;
	i = -1;
	while (++i < size)
		res = (res << 8) + bg[correct_position(addr + i)];
	return (res);
}

int					arg_code(t_uchar argc, int n)
{
	return ((argc >> (6 - (n - 1) * 2)) & 0b11);
}

int					get_arg(t_uchar *bg, t_cursor *cursor, int arg, int code)
{
	if (code == REG_CODE)
		return (uchar_to_int(get_reg_num(cursor, arg), REG_SIZE));
	else if (code == DIR_CODE)
		return (arg);
	if (cursor->op_code != 13)
		return (get_num_by_addr(bg, cursor->position + arg % IDX_MOD,
			REG_SIZE));
	return (get_num_by_addr(bg, cursor->position + arg, REG_SIZE));
}
