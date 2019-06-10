/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:23:44 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/10 18:42:40 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_sep(char *rd, int *i)
{
	while (ft_isspace(rd[*I]) || rd[*I] == SEPARATOR_CHAR)
	{
		if (rd[*I] == '\n')
		{
			g_line++;
			g_readed += (*i);
			(*i) = 1;
			ft_printf("[NEWLINE]\n");
			continue ;
		}
		else if (rd[*I] == SEPARATOR_CHAR)
			ft_printf("[SEPARATOR {%c}]", rd[*I]);
		(*i)++;
	}
}
