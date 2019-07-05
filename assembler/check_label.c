/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:11:14 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/05 20:31:25 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_label(t_list **lst)
{
	(g_counter != 3) ? c_error(lst, SYNTAX) : 1;
	*lst = (*lst)->next;
	if (!(*lst) || (!(*lst && (TTYPE == NEWLINE || TTYPE == INSTRUCTION ||
		TTYPE == COMMENT))))
		c_error(lst, SYNTAX);
}
