/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commandname.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:17:13 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/10 21:03:10 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_commandname(char *rd, int *i, t_list **lst)
{
	char	*test;
	int		j;

	(*i)++;
	j = *I;
	while (islabelchar(rd[*I]))
		(*i)++;
	test = ft_strsub(rd, j, (*I - j));
	ft_printf("[COMMAND NAME {%s}]", test);
	(void)(*lst);
}
