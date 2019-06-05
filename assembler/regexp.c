/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regexp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 21:49:56 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/05 22:06:49 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/* matchhere: search for regexp at beginning of text */
int	matchhere(char *regexp, char *text)
{
	if (regexp[0] == '\0')
		return 1;
	if (regexp[1] == '*')
		return matchstar(regexp[0], regexp+2, text);
	if (regexp[0] == '$' && regexp[1] == '\0')
		return *text == '\0';
	if (*text!='\0' && (regexp[0]=='/' || regexp[0]==*text))
		return matchhere(regexp+1, text+1);
	return 0;
}

/* matchstar: search for c*regexp at beginning of text */
int	matchstar(int c, char *regexp, char *text)
{
	do {    /* a * matches zero or more instances */
		if (matchhere(regexp, text))
			return 1;
	} while (*text != '\0' && (*text++ == c || c == '/'));
	return 0;
}

int	match(char *regexp, char *text)
{
	if (regexp[0] == '^')
		return matchhere(regexp+1, text);
	do {    /* must look even if string is empty */
		if (matchhere(regexp, text))
			return 1;
	} while (*text++ != '\0');
	return 0;
}
