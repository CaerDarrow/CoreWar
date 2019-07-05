/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 17:35:12 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/04 20:52:10 by ajon-hol         ###   ########.fr       */
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

static int	getargsize(int type, int t_dirsize)
{
	if (type == REGISTER)
		return (1);
	else if (type == DIRECT || type == DIRECT_LABEL)
		return ((t_dirsize) ? IND_SIZE : DIR_SIZE);
	else if (type == INDIRECT || type == INDIRECT_LABEL)
		return (IND_SIZE);
	return (0);
}

static void	get_size_and_check_op(t_list **lst, int *size)
{
	t_op	*op;
	int		*k;
	int		i;

	i = -1;
	op = check_opname(lst);
	k = &TOK->argsize;
	*k = -(*size);
	while (i++ < op->argc - 1)
	{
		*lst = (*lst)->next;
		if (TTYPE & op->argv[i])
		{
			TOK->pos[2] = -(*k);
			TOK->argsize = getargsize(TTYPE, op->t_dirsize);
			*size += TOK->argsize;
		}
		else
			c_error(lst, ARG);
		*lst = (*lst)->next;
	}
	*size += op->argtypes + 1;
	*k += *size;
	if (!(*lst && (TTYPE == NEWLINE || TTYPE == COMMENT)))
		c_error(lst, SYNTAX);
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
			TOK->pos[2] = size;
		if (TTYPE == INSTRUCTION)
		{
			TOK->pos[2] = size;
			get_size_and_check_op(lst, &size);
		}
		*lst = (*lst)->next;
	}
	*lst = head;
	return (size);
}
