/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:10:39 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/20 18:35:08 by ajon-hol         ###   ########.fr       */
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
			f_error(lst);
		if (ft_strlen(TOK->token) > PROG_NAME_LENGTH)
			f_error(lst);
	}
	else if (ft_strequ(TOK->token, COMMENT_CMD_STRING) && !(counter & 2))
	{
		counter |= 2;
		*lst = (*lst)->next;
		if (TOK->type != STRING)
			f_error(lst);
		if (ft_strlen(TOK->token) > COMMENT_LENGTH)
			f_error(lst);
	}
	else
		f_error(lst);
	*lst = (*lst)->next;
	if (TOK->type != NEWLINE || TOK->type == COMMENT)
		f_error(lst);
}
