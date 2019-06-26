/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_source_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:48:20 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/26 13:17:55 by jjacobso         ###   ########.fr       */
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

	addr = cursor->position +
		((value[1] = get_arg(entity->bg, cursor, RAW_ARG(2), arg_code(argc, 2))) +
		(value[2] = get_arg(entity->bg, cursor, RAW_ARG(3), arg_code(argc, 3)))) % IDX_MOD;
	reg_num = get_reg_num(cursor,
		(value[0] = RAW_ARG(1)));
	//set_num_by_addr?
	i = -1;
	while (++i < REG_SIZE)
		entity->bg[correct_position(addr + i)] = reg_num[i];
	if (VERBOSE_LVL(4))
	{
		ft_printf("P%5ld | sti r%d %d %d\n", cursor->index, value[0], value[1], value[2]);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", value[1], value[2], value[1] + value[2], (addr));
	}
}

void				clone(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	t_cursor		*new_cursor;
	int				value;

	new_cursor = cursor_create(entity, cursor->id); //cursor copy; make static
	copy_reg(new_cursor->reg, cursor->reg);
	new_cursor->carry = cursor->carry;
	new_cursor->last_live_call = cursor->last_live_call;
	new_cursor->position = correct_position(cursor->position +
		(value = RAW_ARG(1)) % IDX_MOD);
	ld_push_front(&entity->cursors, new_cursor);// push back?
	if (VERBOSE_LVL(4))
		ft_printf("P%5ld | fork %d (%d)\n", cursor->index, value, new_cursor->position);
}

void				lld(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				value[2];

	value[0] = get_arg(entity->bg, cursor, RAW_ARG(1), arg_code(argc, 1));
	value[1] = RAW_ARG(2);
	set_reg_num(cursor, value[1], value[0]);
	set_carry(&cursor->carry, value[0]);
	if (VERBOSE_LVL(4))
		ft_printf("P%5ld | lld %d r%d\n", cursor->index, value[0], value[1]);;
}

void				lldi(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;
	int				addr;
	int				value[3];

	(void)argc;
	addr = cursor->position +
		(value[0] = get_arg(entity->bg, cursor, RAW_ARG(1), arg_code(argc, 1))) +
		(value[1] = get_arg(entity->bg, cursor, RAW_ARG(2), arg_code(argc, 2)));
	num = get_num_by_addr(entity->bg, addr, REG_SIZE);
	set_reg_num(cursor, (value[2] = RAW_ARG(3)), num);
	set_carry(&cursor->carry, num);
	if (VERBOSE_LVL(4))
	{
		ft_printf("P%5ld | lldi %d %d r%d\n", cursor->index, value[0], value[1], value[2]);
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n", value[0], value[1], value[0] + value[1], addr);
	}
}

void				lclone(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	t_cursor		*new_cursor;
	int				value;

	new_cursor = cursor_create(entity, cursor->id); //cursor copy; make static
	copy_reg(new_cursor->reg, cursor->reg);
	new_cursor->carry = cursor->carry;
	new_cursor->last_live_call = cursor->last_live_call;
	new_cursor->position = correct_position(cursor->position +
		(value = RAW_ARG(1)));
	ld_push_front(&entity->cursors, new_cursor);// push back?
	if (VERBOSE_LVL(4))
		ft_printf("P%5ld | lfork %d (%d)\n", cursor->index, value, new_cursor->position);
}
