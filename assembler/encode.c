/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 13:35:51 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/02 21:42:11 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_unit	*encode(t_list **lst, size_t psize)
{
	t_list	 		*head;
	t_unit			*unit;
	unsigned char	*code;
	unsigned char	*codes;

	head = *lst;
	if (!(unit = (t_unit *)malloc(sizeof(t_unit) + sizeof(char[psize]))))
		exit(1);
	code = (unsigned char *)malloc(psize);
	codes = code;
	ft_bzero(unit, (sizeof(t_unit) + sizeof(char[psize])));
	ft_bzero(code, psize);
	set_magic(unit);
	set_prog_size(psize, unit);
	while (*lst)
	{
		// if (TTYPE == COMMAND_NAME)
		// {
		// 	*lst = (*lst)->next;
		// 	set_comment_name(TOKEN, unit, ((t_token *)(*lst)->prev->data)->token);
		// }
		// if (TTYPE == REGISTER)
		// {
		// 	int encoded =0;
		//
		// 	encoded = ft_atoi(TOKEN + 1);
		// 	code = ft_memcpy(code, (void *)&encoded, 1);
		// 	code++;
		// }
		*lst = (*lst)->next;
	}
	set_exec(codes, psize, unit);
	free(codes);
	*lst = head;
	return (unit);
}
