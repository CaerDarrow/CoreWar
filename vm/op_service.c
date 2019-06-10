/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_service.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:55:28 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/10 14:03:29 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

	code = (argc >> (6 - (n - 1) * 2)) & 0b11;
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
	else
		error("Unexpected arg size error ");
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
	///////tmp
	if (size == 2)
		return ((short)res);
	///////
	return (res);
}

int					get_arg(t_uchar argc, t_list *argv, int n, int flag)
{
	return (uchar_to_int(l_get_data(&argv, n), get_arg_size(argc, flag, n)));
}
