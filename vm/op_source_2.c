/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_source_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:47:50 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/13 12:59:10 by jjacobso         ###   ########.fr       */
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
	if (VERBOSE_LVL(4))
		ft_printf("and %d %d %d\n", ARG(1), ARG(2), ARG(3));
}

void				or(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;

	(void)entity;(void)argc;

	num = ARG(1) | ARG(2);
	set_reg_num(cursor, ARG(3), num);
	set_carry(&cursor->carry, num);
	if (VERBOSE_LVL(4))
		ft_printf("or %d %d %d\n", ARG(1), ARG(2), ARG(3));
}

void				xor(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;

	(void)entity;(void)argc;

	num = XOR(ARG(1), ARG(2));
	set_reg_num(cursor, ARG(3), num);
	set_carry(&cursor->carry, num);
	if (VERBOSE_LVL(4))
		ft_printf("xor %d %d %d\n", ARG(1), ARG(2), ARG(3));
}

void				zjmp(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{

	(void)entity;(void)argc;

	if (cursor->carry)
	{
		if (VERBOSE_LVL(4))
			ft_printf("zjmp %d OK\n", ((short)ARG(1)) % IDX_MOD);
		move_cursor(cursor, ((short)ARG(1)) % IDX_MOD);
	}
	else if (VERBOSE_LVL(4))
		ft_printf("zjmp %d FAILED\n", ((short)ARG(1)) % IDX_MOD);
}

void				ldi(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;
	int				addr;

	(void)entity;(void)argc;
	addr = cursor->position + (ARG(1) + ARG(2)) % IDX_MOD;
	num = get_num_by_addr(entity->bg, addr, REG_SIZE);
	set_reg_num(cursor, ARG(3), num);
	if (VERBOSE_LVL(4))
		ft_printf("\tStore %d at %d reg; carry: %d\n", num, addr, cursor->carry);
}
