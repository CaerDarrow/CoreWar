/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encodechamp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 19:43:00 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/03 20:24:48 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_unit	*encodechamp(t_list **lst, size_t psize)
{
	t_list			*head;
	t_unit			*unit;
	unsigned char	*code;

	head = *lst;
	if (!(unit = (t_unit *)ft_memalloc(sizeof(t_unit) + sizeof(char[psize]))))
		exit(1);
	set_magic(unit);
	set_prog_size(psize, unit);
	while (*lst)
	{
		if (TTYPE == COMMAND_NAME)
		{
			*lst = (*lst)->next;
			set_comment_name(TOKEN, unit,
				((t_token *)(*lst)->prev->data)->token);
		}
		*lst = (*lst)->next;
	}
	*lst = head;
	code = encode(lst, psize);
	set_exec(code, psize, unit);
	free(code);
	return (unit);
}
