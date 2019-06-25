/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_source_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:48:20 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/25 16:33:55 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				sti(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	t_uchar			*reg_num;
	int				addr;
	int				i;
	int				value[3];

	(void)argc;

	addr = cursor->position +
		((value[1] = RAW_ARG(2)) +
		(value[2] = RAW_ARG(3))) % IDX_MOD;
	reg_num = get_reg_num(cursor,
		(value[0] = RAW_ARG(1)));
	//set_num_by_addr?
	i = -1;
	while (++i < REG_SIZE)
		entity->bg[correct_position(addr + i)] = reg_num[i];
	if (VERBOSE_LVL(4))
	{
		ft_printf("sti r%d %d %d\n", value[0], value[1], value[2]);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", value[1], value[2], value[1] + value[2], correct_position(addr));
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
	new_cursor->position = correct_position(cursor->position + RAW_ARG(1) % IDX_MOD);
	//something more?
	ld_push_front(&entity->cursors, new_cursor);// push back?
	if (VERBOSE_LVL(4))
		ft_printf("fork %d (%d)\n", RAW_ARG(1), new_cursor->position);
}

void				lld(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				value[2];
	int				num;

	value[0] = RAW_ARG(1);
	(void)entity;(void)argc;
	if (arg_code(argc, 1) == DIR_CODE)
		num = value[0];
	else
		num = get_num_by_addr(entity->bg, cursor->position + value[0], REG_SIZE);
	set_reg_num(cursor, (value[1] = RAW_ARG(2)), num);
	set_carry(&cursor->carry, num);
	if (VERBOSE_LVL(4))
		ft_printf("lld %d r%d\n", value[0], value[1], cursor->carry);
		// ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", value[0], value[1], value[0] + value[1], correct_position(addr));

}

void				lldi(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;
	int				addr;
	int				value[3];

	(void)argc;
	addr = cursor->position +
		(value[0] = RAW_ARG(1)) +
		(value[1] = RAW_ARG(2));
	num = get_num_by_addr(entity->bg, addr, REG_SIZE);
	set_reg_num(cursor, (value[2] = RAW_ARG(3)), num);
	set_carry(&cursor->carry, num);
	if (VERBOSE_LVL(4))
	{
		ft_printf("lldi %d %d r%d\n", value[0], value[1], value[2]);
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", value[0], value[1], value[0] + value[1], correct_position(addr));
	}
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
	new_cursor->position = correct_position(cursor->position + RAW_ARG(1));
	//something more?
	ld_push_front(&entity->cursors, new_cursor);// push back?
	if (VERBOSE_LVL(4))
		ft_printf("lfork %d (%d)\n", RAW_ARG(1), new_cursor->position);

}
