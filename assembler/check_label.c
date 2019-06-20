/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:11:14 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/20 21:01:46 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_label(t_list **lst)
{
	*lst = (*lst)->next;
	if (!(TOK->type == NEWLINE || TOK->type == INSTRUCTION ||
		TOK->type == COMMENT))
		c_error(lst, SYNTAX);
}
