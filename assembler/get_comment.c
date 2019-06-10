/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:14:44 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/10 21:27:29 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_comment(char *rd, int *i, t_list **lst)
{
	int		j;
	t_token	*token;

	j = *I;
	token = inittoken(*i, COMMENT);
	while (!(rd[*I] == '\n' || rd[*I] == '\0'))
		(*i)++;
	token->token = ft_strsub(rd, j, (*I - j));
	ld_push_back(lst, token);
	ft_printf("[token [TOKEN][%03d:%03d] COMMENT \"%s\"]", token->tokpos[0],
	token->tokpos[1], token->token);
}
