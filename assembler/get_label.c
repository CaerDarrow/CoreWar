/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:15:47 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/05 20:19:39 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		get_label(char *rd, int *i, t_list **lst)
{
	t_token	*token;
	int		j;

	(ft_isdigit(rd[*I]) || islabelchar(rd[*I + 1])) ? j = *I : l_error(*i);
	token = inittoken((*i), INSTRUCTION);
	(*i) += (rd[*I] == 'r' || rd[*I] == '-' || rd[*I] == ':') ? 1 : 0;
	while (ft_isdigit(rd[*I]))
		(*i)++;
	if (!islabelchar(rd[*I]) && (rd[*I] != LABEL_CHAR))
	{
		(rd[j] == 'r' && RN(*I - (j + 1), 1, 2)) ? token->type = REGISTER : 5;
		(ft_isdigit(rd[j]) || rd[j] == '-') ? token->type = INDIRECT : 5;
	}
	else
	{
		while (islabelchar(rd[*I]))
			(*i)++;
		if (rd[j] == LABEL_CHAR)
			token->type = INDIRECT | LABEL;
		else if (rd[*I] == LABEL_CHAR)
			token->type = LABEL;
		(*i) += (token->type == LABEL) ? 1 : 0;
	}
	token->token = ft_strsub(rd, j, (*I - j));
	ld_push_back(lst, token);
}
