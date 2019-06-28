/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_source_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:48:54 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/26 14:22:57 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				aff(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	if (entity->print_aff)
	{
		ft_printf("Aff: %c\n", uchar_to_int(get_reg_num(cursor, RAW_ARG(1)), REG_SIZE));
	}
}
