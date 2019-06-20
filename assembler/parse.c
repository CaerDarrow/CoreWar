/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:46:07 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/20 21:26:06 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		g_readed = 0;
int		g_line = 0;

void	(*g_get[11])(char *rd, int *i, t_list **lst) = {
	get_commandname,
	NULL,
	get_direct,
	get_comment,
	get_comment,
	NULL,
	get_sep,
	get_string,
	NULL,
	get_label,
	NULL
};

static int get_command(char *rd, int i)
{
	static char	g_keys[10] = {'.', 0, DIRECT_CHAR, COMMENT_CHAR, ';', 0,
		SEPARATOR_CHAR, '\"', 0, 0};
	size_t 		j;

	j = 0;
	if (islabelchar(rd[I]) || (rd[I] == '-' && ft_isdigit(rd[I + 1])))
		return (9);
	while (j < 10)
	{
		if (rd[I] == g_keys[j])
			return (j);
		j++;
	}
	ft_printf("Lexical error at [%d:%d]\n", g_line + 1, i);
	exit(1);
}

t_list	*parse(char *rd)
{
	int		i;
	int		command;
	t_list	*lst;

	lst = NULL;
	i = 0;
	command = SEP;
	while (rd[I])
	{
		command = SEP;
		g_get[command](rd, &i, &lst);
		if ((command = get_command(rd, i)) != 1)
			g_get[command](rd, &i, &lst);
	}
	return (lst);
}
