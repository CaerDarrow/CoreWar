/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_direct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:19:10 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/04 22:17:06 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		get_direct(char *rd, int *i, t_list **lst)
{
	t_token	*token;
	int		j;

	j = *I;
	token = inittoken((*i)++, 0);
	if (rd[*I] == ':')
	{
		(*i)++;
		if (!(islabelchar(rd[*I])))
			l_error(*i - 2);
		while (islabelchar(rd[*I]))
			(*i)++;
		token->type = DIRECT | LABEL;
	}
	else
	{
		if (!((rd[*I] == '-' && ft_isdigit(rd[*I + 1])) || ft_isdigit(rd[*I])))
			l_error(*i - 1);
		(*i) += (rd[*I] == '-' && ft_isdigit(rd[*I + 1])) ? 1 : 0;
		while (ft_isdigit(rd[*I]))
			(*i)++;
		token->type = DIRECT;
	}
	token->token = ft_strsub(rd, j, (*I - j));
	ld_push_back(lst, token);
}
