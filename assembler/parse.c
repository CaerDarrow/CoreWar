/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:46:07 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/10 19:56:29 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	g_readed = 0;
int	g_line = 0;

int	parse(char *rd)
{
	int i;

	i = 0;
	while (rd[I])
	{
		g_get[SEP](rd, &i);
		if (rd[I] == '.')
			g_get[COMMAND_NAME](rd, &i);
		else if (rd[I] == '\"')
			g_get[STRING](rd, &i);
		else if (islabelchar(rd[I]) || (rd[I] == '-' && ft_isdigit(rd[I + 1])))
			g_get[LABEL](rd, &i);
		else if (rd[I] == COMMENT_CHAR || rd[I] == ';')
			g_get[COMMENT](rd, &i);
		else if (rd[I] == DIRECT_CHAR)
			g_get[DIRECT](rd, &i);
		else if (rd[I])
		{
			ft_printf("Lexical error at [%d:%d]\n", g_line + 1, i);
			exit(1);
		}
	}
	return (1);
}
