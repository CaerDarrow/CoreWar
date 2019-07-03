/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 13:35:51 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/03 20:24:01 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		swap_int(int val, int intflag)
{
	if (intflag)
	{
		val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
		return ((val << 16) | (val >> 16));
	}
	else
		return ((val << 8) | (val >> 8));
}

static void		encodeargs(t_list **lst, unsigned char **code)
{
	unsigned int encoded;

	encoded = ft_atoi(TOKEN + ((TTYPE == DIRECT || TTYPE == REGISTER) ? 1 : 0));
	if (TOK->argsize == DIR_SIZE)
		encoded = swap_int(encoded, 1);
	if (TOK->argsize == IND_SIZE)
		encoded = swap_int((unsigned short)encoded, 0);
	*code = ft_memcpy(*code, (void *)&encoded, TOK->argsize);
	*code += TOK->argsize;
}

static void		encodeargt(t_list **lst, unsigned char **code, int end)
{
	int		i;
	char	encoded;

	encoded = 0;
	i = 1;
	while (i <= 3)
	{
		*lst = (*lst)->next;
		if (i <= end)
		{
			if (TTYPE == REGISTER)
				encoded |= 1;
			else if (TTYPE == DIRECT || TTYPE == DIRECT_LABEL)
				encoded |= 2;
			else if (TTYPE == INDIRECT || TTYPE == INDIRECT_LABEL)
				encoded |= 3;
		}
		encoded = encoded << 2;
		*lst = (*lst)->next;
		i++;
	}
	*code = ft_memcpy(*code, (void *)&encoded, 1);
	*code += 1;
}

static void		encodeinst(t_list **lst, unsigned char **code)
{
	t_op	*op;
	char	encoded;
	t_list	*buf;

	buf = *lst;
	op = check_opname(lst);
	encoded = op->index;
	*code = ft_memcpy(*code, (void *)&encoded, 1);
	*code += 1;
	if (op->argtypes)
		encodeargt(lst, code, op->argc);
	*lst = buf;
}

unsigned char	*encode(t_list **lst, size_t psize)
{
	t_list			*head;
	unsigned char	*code;
	unsigned char	*codestart;

	head = *lst;
	if (!(code = (unsigned char *)ft_memalloc(psize)))
		exit(1);
	codestart = code;
	while (*lst)
	{
		if (TTYPE == INSTRUCTION)
			encodeinst(lst, &code);
		else if (TTYPE == DIRECT || TTYPE == INDIRECT || TTYPE == REGISTER ||
			TTYPE == INDIRECT_LABEL || TTYPE == DIRECT_LABEL)
			encodeargs(lst, &code);
		*lst = (*lst)->next;
	}
	*lst = head;
	return (codestart);
}
