/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_source_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:48:20 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/04 17:41:13 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				sti(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	t_uchar			*reg_num;
	int				addr;
	int				i;
	int				b[3];

	addr = cursor->position +
		((b[1] = get_arg(entity->bg, cursor, RAW_ARG(2), arg_code(argc, 2))) +
		(b[2] = get_arg(entity->bg, cursor, RAW_ARG(3), arg_code(argc, 3)))) %
		IDX_MOD;
	reg_num = get_reg_num(cursor,
		(b[0] = RAW_ARG(1)));
	i = -1;
	while (++i < REG_SIZE)
	{
		entity->vis_key ? entity->SQ->num_sq = correct_position(addr + i) : 0;
		entity->bg[correct_position(addr + i)] = reg_num[i];
		entity->vis_key ? draw_square(entity->vis, cursor->id - 1) : 0;
	}
	if (VERBOSE_LVL(4))
	{
		ft_printf("P%5ld | sti r%d %d %d\n", cursor->index, b[0], b[1], b[2]);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
			b[1], b[2], b[1] + b[2], (addr));
	}
}

void				clone(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	t_cursor		*new_cursor;
	int				b;

	new_cursor = cursor_create(entity, cursor->id);
	copy_reg(new_cursor->reg, cursor->reg);
	new_cursor->carry = cursor->carry;
	new_cursor->last_live_call = cursor->last_live_call;
	new_cursor->position = correct_position(cursor->position +
		(b = RAW_ARG(1)) % IDX_MOD);
	ld_push_front(&entity->cursors, new_cursor);
	if (VERBOSE_LVL(4))
	{
		ft_printf("P%5ld | fork %d (%d)\n", cursor->index, b,
			new_cursor->position);
	}
}

void				lld(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				b[2];

	b[0] = get_arg(entity->bg, cursor, RAW_ARG(1), arg_code(argc, 1));
	b[1] = RAW_ARG(2);
	set_reg_num(cursor, b[1], b[0]);
	set_carry(&cursor->carry, b[0]);
	if (VERBOSE_LVL(4))
	{
		ft_printf("P%5ld | lld %d r%d\n", cursor->index, b[0], b[1]);
	}
}

void				lldi(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;
	int				addr;
	int				b[3];

	(void)argc;
	addr = cursor->position +
		(b[0] = get_arg(entity->bg, cursor, RAW_ARG(1), arg_code(argc, 1))) +
		(b[1] = get_arg(entity->bg, cursor, RAW_ARG(2), arg_code(argc, 2)));
	num = get_num_by_addr(entity->bg, addr, REG_SIZE);
	set_reg_num(cursor, (b[2] = RAW_ARG(3)), num);
	set_carry(&cursor->carry, num);
	if (VERBOSE_LVL(4))
	{
		ft_printf("P%5ld | lldi %d %d r%d\n", cursor->index, b[0], b[1], b[2]);
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
			b[0], b[1], b[0] + b[1], addr);
	}
}

void				lclone(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	t_cursor		*new_cursor;
	int				b;

	new_cursor = cursor_create(entity, cursor->id);
	copy_reg(new_cursor->reg, cursor->reg);
	new_cursor->carry = cursor->carry;
	new_cursor->last_live_call = cursor->last_live_call;
	new_cursor->position = correct_position(cursor->position +
		(b = RAW_ARG(1)));
	ld_push_front(&entity->cursors, new_cursor);
	if (VERBOSE_LVL(4))
	{
		ft_printf("P%5ld | lfork %d (%d)\n", cursor->index, b,
			new_cursor->position);
	}
}
