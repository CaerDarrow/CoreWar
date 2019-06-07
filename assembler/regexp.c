/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regexp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 21:49:56 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/07 20:44:17 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	matchhere(char *regexp, char *text)
{
	if (regexp[0] == '\0')
		return (1);
	if (regexp[1] == '*')
		return (matchstar(regexp[0], regexp + 2, text));
	if (regexp[0] == '$' && regexp[1] == '\0')
		return (*text == '\0');
	if (*text != '\0' && (regexp[0] == '\a' || regexp[0] == *text ||
		(regexp[0] == '\?' && ft_isspace(*text))))
		return (matchhere(regexp + 1, text + 1));
	return (0);
}

int	matchstar(int c, char *regexp, char *text)
{
	if (matchhere(regexp, text))
		return (1);
	while (*text != '\0' && (*text == c || c == '\a' ||
	(c == '\?' && ft_isspace(*text))))
	{
		text++;
		if (matchhere(regexp, text))
			return (1);
	}
	return (0);
}

int	match(char *regexp, char *text)
{
	if (regexp[0] == '^')
		return (matchhere(regexp + 1, text));
	if (matchhere(regexp, text))
		return (1);
	while (*text != '\0')
	{
		text++;
		if (matchhere(regexp, text))
			return (1);
	}
	return (0);
}
