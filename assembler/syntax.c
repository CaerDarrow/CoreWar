/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 17:35:12 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/19 23:44:37 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_op	*check_opname(char *opname)
{
	int i;

	i = 1;
	while (i < 17)
	{
		if (ft_strequ(g_op_tab[i].name, opname))
			return (&g_op_tab[i]);
		i++;
	}
	return (&g_op_tab[0]);
}

static void	f_error(t_list **lst)
{
	printtoken(lst);
	exit(1);
}

static void check_comment(t_list **lst)
{
	t_token *token;

	*lst = (*lst)->next;
	token = (t_token *)(*lst)->data;
	if (token->type != NEWLINE)
		f_error(lst);
}

static void check_command(t_list **lst)
{
	t_token *token;

	*lst = (*lst)->next;
	token = (t_token *)(*lst)->data;
	if (token->type != STRING)
		f_error(lst);
	//Champion name too long (Max length 128)
	//Champion coment too long (Max length 2048)
	*lst = (*lst)->next;
	token = (t_token *)(*lst)->data;
	if (token->type != NEWLINE || token->type == COMMENT)
		f_error(lst);
}

static void check_label(t_list **lst)
{
	t_token *token;

	*lst = (*lst)->next;
	token = (t_token *)(*lst)->data;
	if (!(token->type == NEWLINE || token->type == INSTRUCTION ||
		token->type == COMMENT))
		f_error(lst);
}

static void check_instruction(t_list **lst)
{
	t_op *o;
	t_token *token;
	int i;

	i = 0;
	token = (t_token *)(*lst)->data;
	o = check_opname(token->token);
	if (o == &g_op_tab[0])
		f_error(lst);
	while (i < (o->argc * 2))
	{
		*lst = (*lst)->next;
		token = (t_token *)(*lst)->data;
		if ((!(i & 1) && (!(token->value & o->argv[i / 2]))) || (i != o->argc *
		2 - 1 && (i & 1) && token->type != SEP) || (i == o->argc * 2 - 1 &&
		!(token->type == NEWLINE || token->type == COMMENT)))
			f_error(lst);
		i++;
	}
}

int	syntax(t_list *lst)
{
	t_token *token;

	while (lst)
	{
		token = (t_token *)lst->data;
		if (token->type == NEWLINE)
			lst = lst->next;
		else if (token->type == COMMENT)
			check_comment(&lst);
		else if (token->type == COMMAND_NAME)
			check_command(&lst);
		else if (token->type == LABEL)
			check_label(&lst);
		else if (token->type == INSTRUCTION)
			check_instruction(&lst);
		else
			lst = lst->next;
	}
	return (1);
}
