/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_opname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 19:29:45 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/03 19:30:19 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op	*check_opname(t_list **lst)
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
