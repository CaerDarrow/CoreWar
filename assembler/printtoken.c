/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printtoken.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:05:52 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/02 18:33:40 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	printtoken(t_list **lst)
{
	static char	*type[13] = {"COMMAND", "REGISTER", "DIRECT", "COMMENT",
	"INDERECT", "INSTRUCTION", "SEPARATOR", "STRING", "LABEL", "NEWLINE",
	"DIRECT_LABEL", "", "INDIRECT_LABEL"};

	ft_printf("[TOKEN][%03d:%03d] %s",
				TOK->pos[0], TOK->pos[1], type[TOK->type]);
	if (TOK->type != NEWLINE)
		ft_printf(" \"%s\"", TOK->token);
	ft_printf("{%d, %d}\n", TOK->pos[2], TOK->argsize);
}
