/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:14:54 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/04 21:12:49 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	c_error(t_list **lst, char err)
{
	if (!(*lst))
	{
		ft_printf("Syntax error - unexpected end of input (Perhaps you forgot "
			"to end with a newline ?)\n");
	}
	else if (err == SYNTAX)
	{
		ft_printf("Syntax error at token: ");
		printtoken(lst);
	}
	else if (err == NAMELEN)
		ft_printf("Champion name too long (Max length %d)", PROG_NAME_LENGTH);
	else if (err == COMMENTLEN)
		ft_printf("Champion coment too long (Max length %d)", COMMENT_LENGTH);
	else if (err == ARG)
	{
		ft_printf("Wrong argument type at token: ");
		printtoken(lst);
	}
	else if (err == LBL)
	{
		ft_printf("No such label while attempting to dereference token ");
		printtoken(lst);
	}
	exit(1);
}
