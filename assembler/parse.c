/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:46:07 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/24 17:59:04 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		g_readed = 0;
int		g_line = 0;

void	(*g_get[10])(char *rd, int *i, t_list **lst) = {
	get_commandname,
	NULL,
	get_direct,
	get_comment,
	get_comment,
	NULL,
	get_sep,
	get_string,
	get_label,
	get_label,
};

static int	get_command(char *rd, int i)
{
	static char	g_keys[10] = {'.', 0, DIRECT_CHAR, COMMENT_CHAR, ';', 0,
		SEPARATOR_CHAR, '\"', 0, ':'};
	size_t		j;

	j = 0;
	if (islabelchar(rd[I]) || (rd[I] == '-' && ft_isdigit(rd[I + 1])))
		return (8);
	while (j < 10)
	{
		if (rd[I] == g_keys[j])
			return (j);
		j++;
	}
	ft_printf("Lexical error at [%d:%d]\n", g_line + 1, i);
	exit(1);
}

t_list		*parse(char *rd)
{
	int		i;
	int		command;
	t_list	*lst;

	lst = NULL;
	i = 0;
	command = SEP;
	while (rd[I])
	{
		g_get[command](rd, &i, &lst);
		if ((command = get_command(rd, i)) != 1)
			g_get[command](rd, &i, &lst);
		command = SEP;
	}
	return (lst);
}
