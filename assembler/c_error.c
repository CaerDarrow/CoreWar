/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:14:54 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/20 21:03:27 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	c_error(t_list **lst, char err)
{
	if (err == SYNTAX)
	{
		ft_printf("Syntax error at token: ");
		printtoken(lst);
	}
	if (err == NAMELEN)
		ft_printf("Champion name too long (Max length %d)", PROG_NAME_LENGTH);
	if (err == COMMENTLEN)
		ft_printf("Champion coment too long (Max length %d)", COMMENT_LENGTH);
	if (err == ARG)
	{
		ft_printf("Wrong argument type at token: ");
		printtoken(lst);
	}
	exit(1);
}
