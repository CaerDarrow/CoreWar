/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 21:49:16 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/28 20:58:50 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		set_magic(t_unit *unit)
{
	unit->header.magic = COREWAR_EXEC_MAGIC;
}

void		set_comment_name(char *name, t_unit *unit, char *token)
{
	if (ft_strequ(token, ".name"))
		ft_memcpy(unit->header.prog_name, name, ft_strlen(name));
	if (ft_strequ(token, ".comment"))
		ft_memcpy(unit->header.comment, name, ft_strlen(name));
}

void		set_prog_size(int size, t_unit *unit)
{
	unit->header.prog_size = size;
}

void		set_exec(unsigned char *exec, int size, t_unit *unit)
{
	ft_memcpy(unit->exec, exec, size);
}
