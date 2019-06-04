/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:46:07 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/04 20:16:03 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	parse(char *readed)
{
	int i;
	char *pch;
	//char *prologue;

	i = 0;
	// ft_printf("Lexical error at [%d:%d]\n", i, 1);
	// pch = ft_strtok(readed, ".");
	// prologue = ft_strdup(pch);
	// ft_printf("%s\n", prologue);
	// pch = ft_strtok(0, " ");
	// ft_printf("%s\n", pch);
	// pch = ft_strtok(0, "\"");
	// ft_printf("%s\n", pch);
	// pch = ft_strtok(0, "\"");
	// ft_printf("[%s]\n", pch);
	// pch = ft_strtok(0, ".");
	// ft_printf("%s\n", pch);
	// pch = ft_strtok(0, " ");
	// ft_printf("%s\n", pch);
	// pch = ft_strtok(0, "\"");
	// ft_printf("%s\n", pch);
	// pch = ft_strtok(0, "\"");
	// ft_printf("[%s]\n", pch);
	pch = ft_strtok(readed, "\"\n");
	while (pch != NULL)
	{
		if (ft_strisalpha(pch))
		{
			ft_printf("INSTRUCTION: [%s, %d]\n", pch, i);
		}
		else if (ft_strisnum(pch))
		{
			ft_printf("INDIRECT: [%s, %d]\n", pch, i);
		}
		else if (pch[0] == '%')
		{
			if (ft_strisnum(pch + 1))
				ft_printf("DIRECT: [%s, %d]\n", pch, i);
			else if (pch[1] == ':' && ft_strisalnum(pch + 2))
				ft_printf("DIRECT_LABEL: [%s, %d]\n", pch, i);
		}
		else if (pch[0] == 'r')
		{
			ft_printf("REGISTER: [%s, %d]\n", pch, i);
		}
		else if (pch[ft_strlen(pch) - 1] == ':')
		{
			ft_printf("LABEL: [%s, %d]\n", pch, i);
		}
		else
			ft_printf("ERROR?: [%s, %d]\n", pch, i);
		pch = ft_strtok(NULL, "\"\n");
		i++;
	}
	return (1);
}
