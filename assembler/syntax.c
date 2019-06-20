/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 17:35:12 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/20 18:40:29 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	(*g_check[11])(t_list **lst) = {
	check_command,
	check_comment,
	check_label,
	check_instruction,
	NULL,
	NULL,
	NULL,
	check_newline,
	NULL,
	NULL,
	NULL
};


int	syntax(t_list *lst)
{
	t_token *token;

	while (lst)
	{
		token = (t_token *)lst->data;
		g_check[token->type](&lst);
	}
	return (1);
}
