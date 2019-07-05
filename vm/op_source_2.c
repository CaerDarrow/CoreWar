/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_source_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:47:50 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/04 20:18:33 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				and(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				b[3];
	int				res;

	(void)entity;
	res =
		(b[0] = get_arg(entity->bg, cursor, RAW_ARG(1), arg_code(argc, 1))) &
		(b[1] = get_arg(entity->bg, cursor, RAW_ARG(2), arg_code(argc, 2)));
	set_reg_num(cursor, (b[2] = RAW_ARG(3)), res);
	set_carry(&cursor->carry, res);
	if (VERBOSE_LVL(4))
	{
		ft_printf("P%5ld | and %d %d r%d\n", cursor->index, b[0], b[1], b[2]);
	}
}

void				or(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				b[3];
	int				res;

	(void)entity;
	res =
		(b[0] = get_arg(entity->bg, cursor, RAW_ARG(1), arg_code(argc, 1))) |
		(b[1] = get_arg(entity->bg, cursor, RAW_ARG(2), arg_code(argc, 2)));
	set_reg_num(cursor, (b[2] = RAW_ARG(3)), res);
	set_carry(&cursor->carry, res);
	if (VERBOSE_LVL(4))
	{
		ft_printf("P%5ld | or %d %d r%d\n", cursor->index, b[0], b[1], b[2]);
	}
}

void				xor(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				b[3];
	int				res;

	(void)entity;
	res =
		XOR((b[0] = get_arg(entity->bg, cursor, RAW_ARG(1), arg_code(argc, 1))),
		(b[1] = get_arg(entity->bg, cursor, RAW_ARG(2), arg_code(argc, 2))));
	set_reg_num(cursor, (b[2] = RAW_ARG(3)), res);
	set_carry(&cursor->carry, res);
	if (VERBOSE_LVL(4))
	{
		ft_printf("P%5ld | xor %d %d r%d\n", cursor->index, b[0], b[1], b[2]);
	}
}

void				zjmp(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				b;

	(void)entity;
	b = RAW_ARG(1) % IDX_MOD;
	if (cursor->carry)
	{
		if (VERBOSE_LVL(4))
			ft_printf("P%5ld | zjmp %d OK\n", cursor->index, b);
		move_cursor(entity, cursor, b);
	}
	else if (VERBOSE_LVL(4))
		ft_printf("P%5ld | zjmp %d FAILED\n", cursor->index, b);
}

void				ldi(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;
	int				addr;
	int				b[3];

	addr = cursor->position +
		(((b[0] = get_arg(entity->bg, cursor, RAW_ARG(1), arg_code(argc, 1)))) +
		((b[1] = get_arg(entity->bg, cursor, RAW_ARG(2), arg_code(argc, 2)))))
		% IDX_MOD;
	num = get_num_by_addr(entity->bg, addr, REG_SIZE);
	set_reg_num(cursor, (b[2] = RAW_ARG(3)), num);
	if (VERBOSE_LVL(4))
	{
		ft_printf("P%5ld | ldi %d %d r%d\n", cursor->index, b[0], b[1], b[2]);
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
			b[0], b[1], b[0] + b[1], (addr));
	}
}
