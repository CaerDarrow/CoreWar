/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_source_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:48:20 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/13 13:10:30 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				sti(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	t_uchar			*reg_num;
	int				addr;
	int				i;
	int				position;
	(void)entity;(void)argc;

	addr = cursor->position + (ARG(2) + ARG(3)) % IDX_MOD;
	reg_num = get_reg_num(cursor, ARG(1));
	//set_num_by_addr?
	i = -1;
	while (++i < REG_SIZE)
	{
		position = correct_position(addr + i);
		entity->bg[correct_position(addr + i)] = reg_num[i];
		entity->SQ->num_sq = position;
		draw_square(entity->vis, cursor->id - 1);
	}
	if (VERBOSE_LVL(4))
	{
		ft_printf("sti r%d", ARG(1));
		if (arg_code(argc, 2) == REG_CODE)
			ft_printf(" r%d", ARG(2));
		else
			ft_printf(" %d", ARG(2));
		if (arg_code(argc, 3) == REG_CODE)
			ft_printf(" r%d\n", ARG(3));
		else
			ft_printf(" %d\n", ARG(3));
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", ARG(2), ARG(3), ARG(2) + ARG(3), correct_position(addr));
	}
}

void				clone(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	t_cursor		*new_cursor;
	(void)entity;(void)argc;

	new_cursor = cursor_create(entity, cursor->id); //cursor copy
	copy_reg(new_cursor->reg, cursor->reg);
	new_cursor->carry = cursor->carry;
	new_cursor->last_live_call = cursor->last_live_call;
	new_cursor->position = correct_position(cursor->position + ARG(1) % IDX_MOD);
	//something more?
	ld_push_front(&entity->cursors, new_cursor);// push back?
	if (VERBOSE_LVL(4))
		ft_printf("fork %d\n", ARG(1));
}

void				lld(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;

	(void)entity;(void)argc;
	if (arg_code(argc, 1) == DIR_CODE)
		num = ARG(1);
	else
		num = get_num_by_addr(entity->bg, cursor->position + ARG(1), REG_SIZE);
	set_reg_num(cursor, ARG(2), num);
	set_carry(&cursor->carry, num);
	if (VERBOSE_LVL(4))
		ft_printf("\tStore %d at %d reg; carry: %d\n", num, ARG(2), cursor->carry);
}

void				lldi(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;

	(void)entity;(void)argc;
	num = get_num_by_addr(entity->bg, cursor->position + ARG(1) + ARG(2), REG_SIZE);
	set_reg_num(cursor, ARG(3), num);
	set_carry(&cursor->carry, num);
	if (VERBOSE_LVL(4))
		ft_printf("\tStore %d at %d reg; carry: %d\n", num, ARG(3), cursor->carry);
}

void				lclone(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	t_cursor		*new_cursor;
	(void)entity;(void)argc;

	new_cursor = cursor_create(entity, cursor->id); //cursor copy
	copy_reg(new_cursor->reg, cursor->reg);
	new_cursor->carry = cursor->carry;
	new_cursor->last_live_call = cursor->last_live_call;
	new_cursor->position = correct_position(cursor->position + ARG(1));
	//something more?
	ld_push_front(&entity->cursors, new_cursor);// push back?
	if (VERBOSE_LVL(4))
		ft_printf("\tFork to %d addr\n", new_cursor->position);
}
