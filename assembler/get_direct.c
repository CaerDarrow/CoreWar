/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_direct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:19:10 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/10 21:03:18 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_direct(char *rd, int *i, t_list **lst)
{
	char	*test;
	int		j;

	j = *I;
	(*i)++;
	if (rd[*I] == ':')
	{
		(*i)++;
		while (islabelchar(rd[*I]))
			(*i)++;
		test = ft_strsub(rd, j, (*I - j));
		ft_printf("[DIRECT_LABEL{%s}]", test);
	}
	else
	{
		if (rd[*I] == '-' && ft_isdigit(rd[*I + 1]))
			(*i)++;
		while (ft_isdigit(rd[*I]))
			(*i)++;
		test = ft_strsub(rd, j, (*I - j));
		ft_printf("[DIRECT {%s}]", test);
	}
	(void)(*lst);
}
