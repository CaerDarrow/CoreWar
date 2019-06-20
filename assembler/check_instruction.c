/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:12:16 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/20 21:01:56 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static	t_op	*check_opname(char *opname)
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

void			check_instruction(t_list **lst)
{
	t_op		*op;
	int			i;

	i = 0;
	op = check_opname(TOK->token);
	if (op == &g_op_tab[0])
		c_error(lst, SYNTAX);
	while (i < (op->argc * 2))
	{
		*lst = (*lst)->next;
		if ((!(i & 1) && (!(TOK->type & op->argv[i / 2]))) || (i != op->argc *
		2 - 1 && (i & 1) && TOK->type != SEP) || (i == op->argc * 2 - 1 &&
		!(TOK->type == NEWLINE || TOK->type == COMMENT)))
			c_error(lst, (i & 1) ? SYNTAX : ARG);
		i++;
	}
}
