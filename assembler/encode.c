/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 13:35:51 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/27 17:37:54 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_unit			*initchamp(void)
{
	t_unit	*unit;
	int		psize;

	psize = 22;
	if (!(unit = (t_unit *)malloc(sizeof(t_unit) + sizeof(char[psize]))))
		exit(1);
	ft_bzero(unit, (sizeof(t_unit) + sizeof(char[psize])));
	set_magic(unit);
	set_name("Batman", unit);
	set_prog_size(psize, unit);
	set_comment("This city needs me", unit);
	set_exec((unsigned char *)"aaaaaaaaaaaaaaaaaaaaaa",
	unit->header.prog_size, unit);
	return (unit);
}

t_unit	*encode(t_list **lst)
{
	t_list *head;

	head = *lst;
	while (*lst)
	{
		*lst = (*lst)->next;
	}
	*lst = head;
	return (NULL);
}
