/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:46:07 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/06 18:20:20 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	parse(char **rd)
{
	int i;
	// char *line;
	// char *name;
	// char *comment;

	i = 0;
	while (rd[i])
	{
		// if (match("^\?*.name\?*\"\a*", rd[i]))
		// {
		// 	ft_printf("%s\n", rd[i]);
		// 	while (!match("\"\?*$", rd[i]))
		// 	{
		// 		i++;
		// 		ft_printf("%s\n", rd[i]);
		// 	}
		// }
		// else if (match("^\?*.comment\?*\"\a*", rd[i]))
		// {
		// 	ft_printf("%s\n", rd[i]);
		// 	while (!match("\"\?*$", rd[i]))
		// 	{
		// 		i++;
		// 		ft_printf("%s\n", rd[i]);
		// 	}
		// }
		// else if (ft_strchr(rd[i], '\"'))
		// {
		// 	ft_printf("Error at %d\n", (i + 1));
		// 	return (0);
		// }
		if (match(".\a\?*", rd[i]))
			ft_printf("%s\n", rd[i]);
		i++;
	}
	return (1);
}
