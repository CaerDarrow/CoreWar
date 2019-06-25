/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 17:35:12 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/24 20:29:56 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	(*g_check[10])(t_list **lst) = {
	check_command,
	NULL,
	NULL,
	check_comment,
	NULL,
	check_instruction,
	NULL,
	NULL,
	check_label,
	check_newline,
};

static t_op	*check_opname(t_list **lst)
{
	int i;

	i = 1;
	while (i < 17)
	{
		if (ft_strequ(g_op_tab[i].name, TOKEN))
			return (&g_op_tab[i]);
		i++;
	}
	c_error(lst, SYNTAX);
	return (&g_op_tab[0]);
}

static int	set_tvalue(int type, int t_dirsize)
{
	if (type == REGISTER)
		return (1);
	else if (type == DIRECT || type == DIRECT_LABEL)
		return ((t_dirsize) ? IND_SIZE : DIR_SIZE);
	else if (type == INDIRECT || type == INDIRECT_LABEL)
		return (IND_SIZE);
	return (0);
}

static int	get_size_and_check_op(t_list **lst)
{
	t_op	*op;
	int		*k;
	int		i;

	i = 0;
	op = check_opname(lst);
	k = &TOK->value;
	*k = 1 + op->argtypes;
	while (i < op->argc)
	{
		*lst = (*lst)->next;
		if (TTYPE & op->argv[i])
			TOK->value = set_tvalue(TTYPE, op->t_dirsize);
		else
			c_error(lst, ARG);
		*k += TOK->value;
		*lst = (*lst)->next;
		i++;
	}
	if (!(TTYPE == NEWLINE || TTYPE == COMMENT))
		c_error(lst, SYNTAX);
	return (*k);
}

int			syntax(t_list **lst)
{
	t_list	*head;
	int		size;

	size = 0;
	head = *lst;
	while (*lst)
		g_check[TTYPE](lst);
	*lst = head;
	while (*lst)
	{
		if (TTYPE == LABEL)
			TOK->value = size;
		if (TTYPE == INSTRUCTION)
			size += get_size_and_check_op(lst);
		*lst = (*lst)->next;
	}
	*lst = head;
	return (1);
}
