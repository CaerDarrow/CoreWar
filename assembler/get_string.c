/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:18:31 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/20 20:33:01 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_string(char *rd, int *i, t_list **lst)
{
	t_token	*token;
	int		j;

	token = inittoken((*i)++, STRING);
	j = *I;
	while (rd[*I] != '\"')
	{
		if (rd[*I] == '\n')
		{
			g_line++;
			g_readed += (*i);
			(*i) = 1;
			continue ;
		}
		else if (rd[*I] == '\0')
		{
			ft_printf("Lexical error at [%d:%d]\n", g_line + 1, (*i));
			exit(1);
		}
		(*i)++;
	}
	token->token = ft_strsub(rd, j, (*I - j));
	ld_push_back(lst, token);
	(*i)++;
}
