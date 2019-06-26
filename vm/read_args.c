/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:34:37 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/26 12:35:00 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_uchar		get_dir_size(t_uchar op_code)
{
	if (g_op_tab[op_code].dir)
		return (DIR_SIZE);
	return (IND_SIZE);
}

static int			*get_dir_value(t_uchar *bg, int position, int offset, int size)
{
	return (ft_int_get_mass(get_num_by_addr(bg, position + offset, size)));
}

static int			*get_ind_value(t_uchar *bg, int position, int offset, int op_code)
{
	int				addr;

	addr = (short)get_num_by_addr(bg, position + offset, IND_SIZE);
	if (op_code != 13) /// ...
		addr %= IDX_MOD;
	return (ft_int_get_mass(addr));
}

static int			*get_reg_value(t_uchar *bg, int position, int offset)
{
	int				reg;

	reg = get_num_by_addr(bg, position + offset, 1);
	if (!is_valid_reg(reg))
		return (NULL);
	return (ft_int_get_mass(reg));
}

t_list				*read_args(t_cursor *cursor, t_uchar *bg, t_uchar argc)
{
	int					i;
	int					code;
	int					offset;
	t_list				*res;

	offset = g_op_tab[cursor->op_code].argtypes ? 2 : 1;
	i = 0;
	res = 0;
	while (++i <= g_op_tab[cursor->op_code].argc)
	{
		code = arg_code(argc, i);
		if (code == DIR_CODE)
		{
			ld_push_back(&res, get_dir_value(bg, cursor->position, offset, get_dir_size(cursor->op_code)));
			offset += get_dir_size(cursor->op_code);
		}
		else if (code == IND_CODE)
		{
			ld_push_back(&res, get_ind_value(bg, cursor->position, offset, cursor->op_code));
			offset += IND_SIZE;
		}
		else if (code == REG_CODE)
		{
			if (!get_reg_value(bg, cursor->position, offset))
				return (NULL);
			ld_push_back(&res, get_reg_value(bg, cursor->position, offset));
			offset += 1;
		}
	}
	return (res);
}
