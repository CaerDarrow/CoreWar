/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:10:39 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/05 16:03:24 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_command(t_list **lst)
{
	if (ft_strequ(TOKEN, NAME_CMD_STRING) && !(g_counter & 1))
	{
		g_counter |= 1;
		*lst = (*lst)->next;
		if (!(*lst) || (*lst && TTYPE != STRING))
			c_error(lst, SYNTAX);
		if (ft_strlen(TOKEN) > PROG_NAME_LENGTH)
			c_error(lst, NAMELEN);
	}
	else if (ft_strequ(TOKEN, COMMENT_CMD_STRING) && !(g_counter & 2))
	{
		g_counter |= 2;
		*lst = (*lst)->next;
		if (!(*lst) || (*lst && TTYPE != STRING))
			c_error(lst, SYNTAX);
		if (ft_strlen(TOKEN) > COMMENT_LENGTH)
			c_error(lst, COMMENTLEN);
	}
	else
		c_error(lst, SYNTAX);
	*lst = (*lst)->next;
	if (!(*lst) || (*lst && (TTYPE != NEWLINE || TTYPE == COMMENT)))
		c_error(lst, SYNTAX);
}
