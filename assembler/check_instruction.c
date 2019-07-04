/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:12:16 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/04 21:21:10 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			check_instruction(t_list **lst)
{
	while (!(TTYPE == NEWLINE || TTYPE == COMMENT))
	{
		*lst = (*lst)->next;
		if (!(*lst) || (*lst && !(TTYPE == REGISTER || TTYPE == DIRECT ||
			TTYPE == INDIRECT || TTYPE == DIRECT_LABEL ||
			TTYPE == INDIRECT_LABEL)))
			c_error(lst, ARG);
		*lst = (*lst)->next;
		if (!(*lst) || (*lst && !(TTYPE == SEP ||
			TTYPE == NEWLINE || TTYPE == COMMENT)))
			c_error(lst, SYNTAX);
	}
}
