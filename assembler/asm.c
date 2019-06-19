/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:41:52 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/19 22:22:59 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	printtoken(t_list **parsed)
{
	t_token		*token;
	t_list		*ptr;
	static char	*type[11] = {"SEPARATOR", "COMMAND_NAME", "STRING", "LABEL",
	"COMMENT", "DIRECT", "DIRECT_LABEL", "INSTRUCTION", "REGISTER",
	"INDERECT", "NEWLINE"};

	ptr = *parsed;
	token = (t_token *)ptr->data;
	if (token->type == NEWLINE)
		ft_printf("{[%s][%03d:%03d]}%s",
		type[token->type], token->pos[0], token->pos[1], token->token);
	else
		ft_printf("{[%s][%03d:%03d]\"%s\"}\n",
		type[token->type], token->pos[0], token->pos[1], token->token);
}

static void	lcondel(t_list **parsed)
{
	t_token		*token;

	if (parsed && *parsed && (token = (t_token *)((*parsed)->data)))
	{
		ft_memdel((void **)&token->token);
		ft_memdel((void **)&(*parsed)->data);
	}
}

int			main(int argc, char **argv)
{
	t_unit	*unit;
	t_list	*parsed;
	char	*readed;

	if (argc < 2)
		ft_printf("Usage: ./asm [possible flags] <sourcefile.s>\n");
	else if ((readed = read_s(argv[argc - 1])))
	{
		if ((parsed = parse(readed)))
		{
			if (syntax(parsed))
			{
				unit = initchamp(/*readed*/);
				writechamp(unit, argv[argc - 1]);
				free(unit);
			}
			// l_iter(&parsed, printtoken);
			l_delall(&parsed, lcondel);
		}
		free(readed);
	}
	return (0);
}
