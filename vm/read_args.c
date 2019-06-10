/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:34:37 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/10 16:43:47 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_uchar		get_dir_size(t_uchar op_code)
{
	if (g_op_tab[op_code].t_dirsize)
		return (DIR_SIZE);
	return (IND_SIZE);
}

static t_uchar		*get_num_value(t_uchar *bg, int position, int offset, int size)
{
	int				addr;
	t_uchar	*res;
	int				i;

	if (!(res = (t_uchar	*)ft_strnew(size)))
		error("Malloc error");
	addr = position + offset;
	i = -1;
	while (++i < size)
		res[i] = bg[correct_position(addr + i)];
	return (res);
}

static t_uchar		*get_reg_value(t_uchar *bg, int position, int offset)
{
	int				addr;
	t_uchar			*res;
	int				i;
	int				size;

	size = 1;
	if (!(res = (t_uchar	*)ft_strnew(size)))
		error("Malloc error");
	addr = position + offset;
	i = -1;
	while (++i < size)
		res[i] = bg[correct_position(addr + i)];
	return (res);
}

t_list				*read_args(t_cursor *cursor, t_uchar *bg, t_uchar argc)
{
	int					i;
	int					code;
	int					offset;
	t_list				*res;

	offset = g_op_tab[cursor->op_code].argtypes ? 2 : 1;
	i = -1;
	res = 0;
	while (++i < g_op_tab[cursor->op_code].argc)
	{
		code = arg_type(argc, i);
		if (code == DIR_CODE)
		{
			ld_push_back(&res, get_num_value(bg, cursor->position, offset, get_dir_size(cursor->op_code)));
			offset += get_dir_size(cursor->op_code);
		}
		else if (code == IND_CODE)
		{
			ld_push_back(&res, get_num_value(bg, cursor->position, offset, IND_SIZE));
			offset += IND_SIZE;
		}
		else if (code == REG_CODE)
		{
			ld_push_back(&res, get_reg_value(bg, cursor->position, offset));
			offset += 1;
		}
	}
	return (res);
}
