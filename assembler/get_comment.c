/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:14:44 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/11 17:23:38 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_comment(char *rd, int *i, t_list **lst)
{
	t_token	*token;
	int		j;

	j = *I;
	token = inittoken(*i, COMMENT);
	while (!(rd[*I] == '\n' || rd[*I] == '\0'))
		(*i)++;
	token->token = ft_strsub(rd, j, (*I - j));
	ld_push_back(lst, token);
}
