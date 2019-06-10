/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:15:47 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/10 21:03:25 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	issep(char c)
{
	if (c == SEPARATOR_CHAR || ft_isspace(c) || c == '\0')
		return (1);
	return (0);
}

void		get_label(char *rd, int *i, t_list **lst)
{
	char	*test;
	int		j;

	j = *I;
	if (rd[*I] == 'r' || rd[*I] == '-')
		(*i)++;
	while (ft_isdigit(rd[*I]))
		(*i)++;
	if (issep(rd[*I]))
	{
		test = ft_strsub(rd, j, (*I - j));
		if (rd[j] == 'r' && (*I - (j + 1)) < 3)
			ft_printf("[REGISTER {%s}]", test);
		else if (ft_isdigit(rd[j]) || rd[j] == '-')
			ft_printf("[INDERECT {%s}]", test);
	}
	else
	{
		while (islabelchar(rd[*I]))
			(*i)++;
		test = ft_strsub(rd, j, (*I - j));
		if (rd[*I] != LABEL_CHAR)
			ft_printf("[INSTRUCTION {%s}]", test);
		else if ((*i)++)
			ft_printf("[LABEL {%s}]", test);
	}
	(void)(*lst);
}
