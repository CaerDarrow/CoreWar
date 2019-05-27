/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 21:49:16 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/05/27 20:44:21 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	swapped(int num)
{
	int swapped;

	swapped = ((num >> 24) & 0xff) | ((num << 8) & 0xff0000) |
	((num >> 8) & 0xff00) | ((num << 24) & 0xff000000);
	return (swapped);
}

void		set_magic(t_unit *unit)
{
	unit->header.magic = swapped(COREWAR_EXEC_MAGIC);
}

void		set_name(char *name, t_unit *unit)
{
	ft_memcpy(unit->header.prog_name, name, ft_strlen(name));
}

void		set_prog_size(int size, t_unit *unit)
{
	unit->header.prog_size = swapped(size);
}

void		set_comment(char *comment, t_unit *unit)
{
	ft_memcpy(unit->header.comment, comment, ft_strlen(comment));
}
