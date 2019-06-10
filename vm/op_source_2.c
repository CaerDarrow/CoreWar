/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_source_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:47:50 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/10 19:45:29 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				and(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;

	(void)entity;(void)argc;
	num = ARG(1) & ARG(2);
	set_reg_num(cursor, ARG(3), num);
	set_carry(&cursor->carry, num);
}

void				or(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;

	(void)entity;(void)argc;

	num = ARG(1) | ARG(2);
	set_reg_num(cursor, ARG(3), num);
	set_carry(&cursor->carry, num);
}

void				xor(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;

	(void)entity;(void)argc;

	num = XOR(ARG(1), ARG(2));
	set_reg_num(cursor, ARG(3), num);
	set_carry(&cursor->carry, num);
}

void				zjmp(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{

	(void)entity;(void)argc;

	if (cursor->carry)
		move_cursor(cursor, ARG(1));
	if (g_verbose > 0)
		ft_printf("Player's cursor %d at %d; arg: %d\n", cursor->id, cursor->position, ARG(1));
}

void				ldi(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;

	(void)entity;(void)argc;

 	num = (ARG(1) + ARG(2)) % IDX_MOD;
	set_reg_num(cursor, num, ARG(2));
	set_carry(&cursor->carry, num);
}
