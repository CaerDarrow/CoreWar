/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inittoken.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 21:18:04 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/02 18:23:21 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token	*inittoken(int strpos, int type)
{
	t_token	*token;

	if (!(token = (t_token *)malloc(sizeof(*token))))
		exit(1);
	token->pos[0] = g_line + 1;
	token->pos[1] = strpos;
	token->pos[2] = 0;
	token->argsize = 0;
	token->type = type;
	return (token);
}
