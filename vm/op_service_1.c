/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_service_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:55:28 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/06 18:12:31 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_uchar				get_dir_size(t_uchar op_code)
{
	if (g_op_tab[op_code].dir)
		return (DIR_SIZE);
	return (IND_SIZE);
}

void				set_carry(char *carry, int num)
{
	if (num == 0)
		*carry = 1;
	else
		*carry = 0;
}

int					get_arg_size(t_uchar argc, int flag, int n)
{
	int				code;

	code = arg_code(argc, n);
	if (code == DIR_CODE)
	{
		if (flag)
			return (DIR_SIZE);
		return (IND_SIZE);
	}
	else if (code == IND_CODE)
		return (IND_SIZE);
	else if (code == REG_CODE)
		return (1);
	return (0);
}

int					uchar_to_int(t_uchar *s, int size)
{
	int				i;
	int				res;

	res = 0;
	i = -1;
	while (++i < size)
		res = (res << 8) | s[i];
	if (size == 2)
		return ((short)res);
	return (res);
}
