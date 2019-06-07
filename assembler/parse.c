/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:46:07 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/07 20:51:53 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	g_readed = 0;
static int	g_line = 0;

int			islabelchar(char c)
{
	if (ft_strchr(LABEL_CHARS, c))
		return (1);
	return (0);
}

int			issep(char c)
{
	if (c == SEPARATOR_CHAR || ft_isspace(c) || c == '\0')
		return(1);
	return (0);
}

void		skipspaces(char *rd, int *i)
{
	while (ft_isspace(rd[*I]))
	{
		if (rd[*I] == '\n')
		{
			g_line++;
			g_readed += (*i);
			(*i) = 1;
			//ft_printf("[NEWLINE]\n");
			continue ;
		}
		(*i)++;
	}
}

void		get_commandname(char *rd, int *i)
{
	char *test;
	int j;

	(*i)++;
	j = *I;
	while (islabelchar(rd[*I]))
		(*i)++;
	test = ft_strsub(rd, j, (*I - j));
	//ft_printf("[COMMAND NAME {%s}]", test);
}

void		get_string(char *rd, int *i)
{
	char *test;
	int j;

	(*i)++;
	j = *I;
	while (rd[*I] != '\"')
	{
		if (rd[*I] == '\n')
		{
			g_line++;
			g_readed += (*i);
			(*i) = 1;
			continue ;
		}
		(*i)++;
	}
	test = ft_strsub(rd, j, (*I - j));
	//ft_printf("[STRING {%s}]", test);
	(*i)++;
}

void		get_comment(char *rd, int *i)
{
	char *test;
	int j;

	j = *I;
	while (!(rd[*I] == '\n' || rd[*I] == '\0'))
		(*i)++;
	test = ft_strsub(rd, j, (*I - j));
	//ft_printf("[COMMENT {%s}]", test);
}

void		get_direct(char *rd, int *i)
{
	char *test;
	int j;

	j = *I;
	/*:direct or number*/
	while (!issep(rd[*I]))
			(*i)++;
	test = ft_strsub(rd, j, (*I - j));
	if (test[1] == ':')
		;//ft_printf("[DIRECT LABEL{%s}]", test);
	else
		;//ft_printf("[DIRECT {%s}]", test);
}

void		get_label(char *rd, int *i)
{
	char *test;
	int j;

	j = *I;
	if (rd[*I] == 'r')
		(*i)++;
	while (ft_isdigit(rd[*I]))
		(*i)++;
	if (issep(rd[*I]))
	{
		test = ft_strsub(rd, j, (*I - j));
		if (rd[j] == 'r' && (*I - (j + 1)) < 3)
			;//ft_printf("[REGISTER {%s}]", test);
		else if (ft_isdigit(rd[j]))
			;//ft_printf("[INDERECT {%s}]", test);
	}
	else
	{
		while (islabelchar(rd[*I]))
			(*i)++;
		test = ft_strsub(rd, j, (*I - j));
		if (rd[*I] == LABEL_CHAR)
		{
			//ft_printf("[LABEL {%s}]", test);
			(*i)++;
		}
		else
			;//ft_printf("[INSTRUCTION {%s}]", test);
	}
}

int	parse(char *rd)
{
	int i;

	i = 0;
	while (rd[I])
	{
		skipspaces(rd, &i);
		if (rd[I] == '.')
			get_commandname(rd, &i);
		else if (rd[I] == '\"')
			get_string(rd, &i);
		else if (islabelchar(rd[I]))
			get_label(rd, &i);
		else if (rd[I] == COMMENT_CHAR || rd[I] == ';')
			get_comment(rd, &i);
		else if (rd[I] == DIRECT_CHAR)
			get_direct(rd, &i);
		else if (rd[I] == SEPARATOR_CHAR)
			i++;
		else if (rd[I])
		{
			ft_printf("Lexical error at [%d:%d]\n", g_line + 1, i);
			return (0);
		}
	}
	return (1);
}
