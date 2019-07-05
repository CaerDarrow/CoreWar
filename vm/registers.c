/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:37:01 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/04 18:12:52 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			set_reg_num(t_cursor *cursor, int n, int value)
{
	int			i;

	i = -1;
	if (!is_valid_reg(n))
		error("Invalid register");
	while (++i < REG_SIZE)
		cursor->reg[n - 1][i] = (value >> (32 - 8 * (i + 1))) & 0xFF;
}

t_uchar			*get_reg_num(t_cursor *cursor, int n)
{
	if (!is_valid_reg(n))
		error("Invalid register");
	return (cursor->reg[n - 1]);
}
