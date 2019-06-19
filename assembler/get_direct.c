/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_direct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:19:10 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/19 23:03:30 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_direct(char *rd, int *i, t_list **lst)
{
	t_token	*token;
	int		j;

	j = *I;
	token = inittoken((*i)++, 0);
	if (rd[*I] == ':')
	{
		(*i)++;
		while (islabelchar(rd[*I]))
			(*i)++;
		token->type = DIRECT_LABEL;
	}
	else
	{
		if (rd[*I] == '-' && ft_isdigit(rd[*I + 1]))
			(*i)++;
		while (ft_isdigit(rd[*I]))
			(*i)++;
		token->type = DIRECT;
	}
	token->value = T_DIR;
	token->token = ft_strsub(rd, j, (*I - j));
	ld_push_back(lst, token);
}
