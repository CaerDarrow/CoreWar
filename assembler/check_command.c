/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:10:39 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/20 21:03:12 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_command(t_list **lst)
{
	static int	counter = 0;

	if (ft_strequ(TOK->token, NAME_CMD_STRING) && !(counter & 1))
	{
		counter |= 1;
		*lst = (*lst)->next;
		if (TOK->type != STRING)
			c_error(lst, SYNTAX);
		if (ft_strlen(TOK->token) > PROG_NAME_LENGTH)
			c_error(lst, NAMELEN);
	}
	else if (ft_strequ(TOK->token, COMMENT_CMD_STRING) && !(counter & 2))
	{
		counter |= 2;
		*lst = (*lst)->next;
		if (TOK->type != STRING)
			c_error(lst, SYNTAX);
		if (ft_strlen(TOK->token) > COMMENT_LENGTH)
			c_error(lst, COMMENTLEN);
	}
	else
		c_error(lst, SYNTAX);
	*lst = (*lst)->next;
	if (TOK->type != NEWLINE || TOK->type == COMMENT)
		c_error(lst, SYNTAX);
}
