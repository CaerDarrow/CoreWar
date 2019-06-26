/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_source_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:48:54 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/26 13:17:57 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				aff(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	t_uchar			*str;

	if (entity->print_aff)
	{
		str = get_reg_num(cursor, RAW_ARG(1));
		if (VERBOSE_LVL(4))
			ft_printf("P%5ld | aff\n", cursor->index);
		write(1, str, 4);
		write(1, "\n", 1);
	}
}
