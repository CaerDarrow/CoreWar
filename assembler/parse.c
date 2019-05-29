/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:46:07 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/05/29 22:23:41 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// typedef struct	s_parsed
// {
// 	char		*label;
// 	char		*instruction;
// 	char		*register;
// 	char		*separator;
// 	char		*direct;
// 	char		*direct_label;
// 	char		*string;
// }				t_parsed;

static int	skipspaces(int i, char *line)
{
	while (ft_isspace(line[i]))
		i++;
	return (i);
}

int	parse(char **readed)
{
	int i;
	int j;
	char *line;

	i = 0;
	while ((line = readed[i]) && i < 10)
	{
		ft_printf("[%s]\n", line);
		j = 0;
		j = skipspaces(j, line);
		if (ft_strequ(line, ""))
			;
		else if (line[j] == '#' || line[j] == ';')
			ft_printf("Comment: %s\n", (line + j));
		else if (line[j] == '.')
		{
			j = skipspaces(j, line);
			if (ft_strnequ((line + j), ".name", 5))
			{
				ft_printf("Name: %s\n", (line + j));
				j = skipspaces(j, (line + j));
				if (line[j] != '\"')
					ft_printf("Lexical error at [%d:%d]\n", i, j);
			}
			else if (ft_strnequ((line + j), ".comment", 8))
			{
				ft_printf("Comment: %s\n", (line + j));
				j = skipspaces(j, line);
				if (line[j] != '\"')
					ft_printf("Lexical error at [%d:%d]\n", i, j);
			}
			else
				ft_printf("Error string\n");
		}
		i++;
	}
	return (1);
}
