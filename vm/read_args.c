/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:34:37 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/04 19:16:33 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			*get_ind_value(t_uchar *bg, int position, int offset)
{
	int				addr;

	addr = (short)get_num_by_addr(bg, position + offset, IND_SIZE);
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

void				read_dir_value(t_list **res, t_uchar *bg, t_cursor *cursor,
						int *offset)
{
	int				size;

	size = get_dir_size(cursor->op_code);
	ld_push_back(res, ft_int_get_mass(
		get_num_by_addr(bg, cursor->position + *offset, size)));
	*offset += size;
}

void				read_ind_value(t_list **res, t_uchar *bg, t_cursor *cursor,
						int *offset)
{
	ld_push_back(res, get_ind_value(bg, cursor->position, *offset));
	*offset += IND_SIZE;
}

int					read_reg_value(t_list **res, t_uchar *bg, t_cursor *cursor,
						int *offset)
{
	int					*buff;

	if (!(buff = get_reg_value(bg, cursor->position, *offset)))
		return (0);
	ld_push_back(res, buff);
	*offset += 1;
	return (1);
}
