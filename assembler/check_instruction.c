/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:12:16 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/24 20:23:26 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			check_instruction(t_list **lst)
{
	int i;

	i = 0;
	while (!(TTYPE == NEWLINE || TTYPE == COMMENT))
	{
		*lst = (*lst)->next;
		if ((!(i & 1) && !(TTYPE == REGISTER || TTYPE == DIRECT || TTYPE ==
		INDIRECT || TTYPE == DIRECT_LABEL || TTYPE == INDIRECT_LABEL)) ||
		((i & 1) && !(TTYPE == SEP || TTYPE == NEWLINE || TTYPE == COMMENT)))
			c_error(lst, ARG);
		i++;
	}
}
