/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 13:35:51 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/03 19:02:02 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int swap_int(int val)
{
	val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

static short swap_short(int val)
{
	return (val << 8) | (val >> 8);
}

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

t_unit	*encode(t_list **lst, size_t psize)
{
	t_list	 		*head;
	t_unit			*unit;
	unsigned char	*code;
	unsigned char	*codes;
	int i = 0;
	t_list	 *buf;

	head = *lst;
	if (!(unit = (t_unit *)malloc(sizeof(t_unit) + sizeof(char[psize]))))
		exit(1);
	ft_bzero(unit, (sizeof(t_unit) + sizeof(char[psize])));
	code = (unsigned char *)malloc(psize);
	codes = code;
	ft_bzero(code, psize);
	set_magic(unit);
	set_prog_size(psize, unit);
	while (*lst)
	{
		if (TTYPE == COMMAND_NAME)
		{
			*lst = (*lst)->next;
			set_comment_name(TOKEN, unit, ((t_token *)(*lst)->prev->data)->token);
		}
		else if (TTYPE == INSTRUCTION)
		{
			t_op *op = check_opname(lst);
			char encoded = op->index;
			code = ft_memcpy(code, (void *)&encoded, 1);
			code++;
			if (op->argtypes)
			{
				buf = *lst;
				char encoded = 0;
				i = 1;
				while (i <= 3)
				{
					*lst = (*lst)->next;
					if (i <= op->argc)
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
				*lst = buf;
				code = ft_memcpy(code, (void *)&encoded, 1);
				code++;
			}
		}
		else if (TTYPE == REGISTER)
		{
			char encoded = ft_atoi(TOKEN + 1);
			code = ft_memcpy(code, &encoded, TOK->argsize);
			code += TOK->argsize;
		}
		else if (TTYPE == DIRECT || TTYPE == INDIRECT || TTYPE == INDIRECT_LABEL ||
			TTYPE == DIRECT_LABEL)
		{

			unsigned int encoded;

			encoded = ft_atoi(TOKEN + ((TTYPE == DIRECT) ? 1 : 0));
			if (TOK->argsize == DIR_SIZE)
				encoded = swap_int(encoded);
			if (TOK->argsize == IND_SIZE)
				encoded = swap_short((unsigned short)encoded);
			code = ft_memcpy(code, (void *)&encoded, TOK->argsize);
			code += TOK->argsize;
		}
		*lst = (*lst)->next;
	}
	set_exec(codes, psize, unit);
	free(codes);
	*lst = head;
	return (unit);
}
