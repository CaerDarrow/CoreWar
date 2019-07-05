/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:11:14 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/05 16:07:51 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_label(t_list **lst)
{
	if (g_counter != 3)
		c_error(lst, SYNTAX);
	*lst = (*lst)->next;
	if (!(*lst) || (!(*lst && (TTYPE == NEWLINE || TTYPE == INSTRUCTION ||
		TTYPE == COMMENT))))
		c_error(lst, SYNTAX);
}
