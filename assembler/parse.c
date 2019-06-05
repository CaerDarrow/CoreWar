/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:46:07 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/05 22:08:08 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// char *take_delim(char **readed)
// {
// 	while (**readed)
// 	{
// 		if (**readed == COMMENT_CHAR)
// 			return ("\0");
// 		else if (**readed == '.')
// 			return (" \t");
// 		else if (**readed == '\"')
// 		{
// 			(*readed)++;
// 			return ("\"");
// 		}
// 		else if (ft_isalpha(**readed))
// 			return (" ,:\t");
// 		else if (**readed == 'r')
// 			return (",\0");
// 		else if (**readed == DIRECT_CHAR)
// 			return (",\0");
// 		else if (ft_isdigit(**readed))
// 			return (",\0");
// 		(*readed)++;
// 	}
// 	return(NULL);
// }

int	parse(char **readed)
{
	int i;
	char *line;
	// char *pch;
	// char *delim;
	// char *reentry;

	i = 0;
	while (readed[i] && (line = ft_strdup(readed[i])))
	{
		// reentry = NULL;
		// delim = take_delim(&line);
		// pch = lexer(line, delim, &reentry);
		// while (pch != NULL)
		// {
		// 	line += (ft_strlen(pch) + 1);
		// 	delim = take_delim(&line);
		// 	ft_printf("[%s]\n");
		// 	pch = lexer(line, delim, &reentry);
		// 	getchar();
		// }
		// ft_printf("__________________\n");
		if (*line && match("#/*$", line))
			ft_printf("%s\n", line);
		i++;
	}
	return (1);
}
