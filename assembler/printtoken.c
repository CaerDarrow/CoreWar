/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printtoken.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:05:52 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/20 18:46:09 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	printtoken(t_list **lst)
{
	static char	*type[11] = {"COMMAND", "COMMENT", "LABEL", "INSTRUCTION",
	"SEPARATOR", "STRING", "DIRECT", "NEWLINE", "DIRECT_LABEL",
	"REGISTER", "INDERECT"};


	ft_printf("[TOKEN][%03d:%03d] %s",
				TOK->pos[0], TOK->pos[1], type[TOK->type]);
	if (TOK->type != NEWLINE)
		ft_printf(" \"%s\"", TOK->token);
	ft_printf("\n");
}
