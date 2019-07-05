/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:12:16 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/05 20:31:13 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			check_instruction(t_list **lst)
{
	(g_counter != 3) ? c_error(lst, SYNTAX) : 1;
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
