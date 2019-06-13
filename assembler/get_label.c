/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:15:47 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/11 17:15:28 by ajon-hol         ###   ########.fr       */
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
	t_token	*token;
	int		j;

	j = *I;
	token = inittoken((*i), INSTRUCTION);
	(*i) += (rd[*I] == 'r' || rd[*I] == '-') ? 1 : 0;
	while (ft_isdigit(rd[*I]))
		(*i)++;
	if (issep(rd[*I]))
	{
		token->token = ft_strsub(rd, j, (*I - j));
		if (rd[j] == 'r' && (*I - (j + 1)) < 3)
			token->type = REGISTER;
		else if (ft_isdigit(rd[j]) || rd[j] == '-')
			token->type = INDERECT;
	}
	else
	{
		while (islabelchar(rd[*I]))
			(*i)++;
		token->token = ft_strsub(rd, j, (*I - j));
		token->type = (rd[*I] != LABEL_CHAR) ? INSTRUCTION : LABEL;
		(*i) += (rd[*I] == LABEL_CHAR) ? 1 : 0;
	}
	ld_push_back(lst, token);
}