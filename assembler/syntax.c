/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 17:35:12 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/12 17:43:16 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	syntax(t_list *lst)
{
	t_token *token;
	static char	*type[11] = {"SEPARATOR", "COMMAND_NAME", "STRING", "LABEL",
	"COMMENT", "DIRECT", "DIRECT_LABEL", "INSTRUCTION", "REGISTER",
	"INDERECT", "NEWLINE"};

	while (lst)
	{
		token = (t_token *)lst->data;
		if (token->type == NEWLINE)
			lst = lst->next;
		else if (token->type == COMMENT)
		{
			lst = lst->next;
			token = (t_token *)lst->data;
			if (token->type != NEWLINE)
			{
				ft_printf("{[%s][%03d:%03d]\"%s\"}",
				type[token->type], token->pos[0], token->pos[1], token->token);
				return (0);
			}
		}
		else if (token->type == COMMAND_NAME)
		{
			lst = lst->next;
			token = (t_token *)lst->data;
			if (token->type != STRING)
			{
				ft_printf("{[%s][%03d:%03d]\"%s\"}",
				type[token->type], token->pos[0], token->pos[1], token->token);
				return (0);
			}
			//Champion name too long (Max length 128)
			//Champion coment too long (Max length 2048)
			lst = lst->next;
			token = (t_token *)lst->data;
			if (token->type != NEWLINE || token->type == COMMENT)
			{
				ft_printf("{[%s][%03d:%03d]\"%s\"}",
				type[token->type], token->pos[0], token->pos[1], token->token);
				return (0);
			}
		}
		else if (token->type == LABEL)
		{
			lst = lst->next;
			token = (t_token *)lst->data;
			if (!(token->type == NEWLINE || token->type == INSTRUCTION ||
				token->type == COMMENT))
			{
				ft_printf("{[%s][%03d:%03d]\"%s\"}\n",
				type[token->type], token->pos[0], token->pos[1], token->token);
				return (0);
			}
		}
		else if (token->type == INSTRUCTION)
		{
			lst = lst->next;
			token = (t_token *)lst->data;
			if (!(token->type == NEWLINE || token->type == INSTRUCTION ||
				token->type == COMMENT))
			{
				ft_printf("{[%s][%03d:%03d]\"%s\"}\n",
				type[token->type], token->pos[0], token->pos[1], token->token);
				return (0);
			}
		}
	}
	return (1);
}
