/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_source_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:48:54 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/25 16:34:45 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				aff(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	(void)entity;(void)argc;

	ft_printf("aff %d\n", uchar_to_int(get_reg_num(cursor, RAW_ARG(1)), REG_SIZE));
}
