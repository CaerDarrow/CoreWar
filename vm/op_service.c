/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_service.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:55:28 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/07 19:56:08 by jjacobso         ###   ########.fr       */
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

// // merge get arg f
// int					get_arg1(t_uchar argc, t_list *argv, int flag)
// {
// 	int				res;
// 	t_uchar			*s;
//
// 	s = (t_uchar	*)l_get_data(&argv, 1);
// 	res = uchar_to_int(s, get_arg_size(argc, flag, 1));
// 	// while (++i < size)
// 	// {
// 	// 	res = (res << 8) | s[i];
// 	// }
// 		// ft_printf("1:%d %s num = %d size = %d \n", res, s, get_num(s, size), size);
// 	// if ((s[0] >> 7) & 0b1)
// 	// 	return (-res);
// 	return (res);
// }
//
// int					get_arg2(t_uchar argc, t_list *argv, int flag)
// {
// 	int				size;
// 	int				i;
// 	int				res;
// 	t_uchar	*s;
//
// 	s = (t_uchar	*)l_get_data(&argv, 2);
// 	size = get_arg_size(argc, flag, 2);
// 	res = 0;
// 	i = -1;
// 	//unsigned ot int func
// 	while (++i < size)
// 		res = (res << 8) | s[i];
// 		// ft_printf("2:%d %s num = %d size = %d\n", res, s, get_num(s , size), size);
//
// 	return (res);
// }
//
// int					get_arg3(t_uchar argc, t_list *argv, int flag)
// {
// 	int				size;
// 	int				i;
// 	int				res;
// 	t_uchar	*s;
//
// 	s = (t_uchar	*)l_get_data(&argv, 3);
// 	size = get_arg_size(argc, flag, 3);
// 	res = 0;
// 	i = -1;
// 	while (++i < size)
// 		res = (res << 8) | s[i];
// 		// ft_printf("1dddddddddd%d\n", argv[offset]);
// 		// ft_printf("3:%d %s num = %d size = %d\n", res, s, get_num(s, size), size);
// 	return (res);
// }
