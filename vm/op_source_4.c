/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_source_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:48:54 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/10 19:30:11 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				aff(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	(void)entity;(void)argc;

	ft_printf("%s\n", get_reg_num(cursor, ARG(1)));
}
