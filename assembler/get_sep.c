/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:23:44 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/13 18:10:46 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_sep(char *rd, int *i, t_list **lst)
{
	t_token	*token;

	while (ft_isspace(rd[*I]) || rd[*I] == SEPARATOR_CHAR)
	{
		if (rd[*I] == '\n')
		{
			token = inittoken(*i, NEWLINE);
			token->token = ft_strdup("\n");
			ld_push_back(lst, token);
			g_readed += (*i);
			(*i) = 1;
			g_line++;
			continue ;
		}
		else if (rd[*I] == SEPARATOR_CHAR)
		{
			token = inittoken(*i, SEP);
			token->token = ft_strdup(",");
			ld_push_back(lst, token);
		}
		(*i)++;
	}
}
