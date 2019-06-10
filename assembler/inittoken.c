/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inittoken.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 21:18:04 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/10 21:28:05 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token	*inittoken(int strpos, int type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(*token));
	token->tokpos[0] = g_line + 1;
	token->tokpos[1] = strpos;
	token->toktype = type;
	return (token);
}
