/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_source_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:47:50 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/26 13:17:52 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				and(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				value[3];
	int				res;

	(void)entity;
	res =
		(value[0] = get_arg(entity->bg, cursor, RAW_ARG(1), arg_code(argc, 1))) &
		(value[1] = get_arg(entity->bg, cursor, RAW_ARG(2), arg_code(argc, 2)));
	set_reg_num(cursor, (value[2] = RAW_ARG(3)), res);
	set_carry(&cursor->carry, res);
	if (VERBOSE_LVL(4))
	{
		ft_printf("P%5ld | and %d %d r%d\n", cursor->index, value[0], value[1], value[2]);
	}
}

void				or(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				value[3];
	int				res;

	(void)entity;
	res =
		(value[0] = get_arg(entity->bg, cursor, RAW_ARG(1), arg_code(argc, 1))) |
		(value[1] = get_arg(entity->bg, cursor, RAW_ARG(2), arg_code(argc, 2)));
	set_reg_num(cursor, (value[2] = RAW_ARG(3)), res);
	set_carry(&cursor->carry, res);
	if (VERBOSE_LVL(4))
	{
		ft_printf("P%5ld | or %d %d r%d\n", cursor->index, value[0], value[1], value[2]);
	}
}

void				xor(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				value[3];
	int				res;

	(void)entity;
	res =
		XOR((value[0] = get_arg(entity->bg, cursor, RAW_ARG(1), arg_code(argc, 1))),
		(value[1] = get_arg(entity->bg, cursor, RAW_ARG(2), arg_code(argc, 2))));
	set_reg_num(cursor, (value[2] = RAW_ARG(3)), res);
	set_carry(&cursor->carry, res);
	if (VERBOSE_LVL(4))
	{
		ft_printf("P%5ld | xor %d %d r%d\n", cursor->index, value[0], value[1], value[2]);
	}
}

void				zjmp(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{

	(void)entity;(void)argc;

	// if (cursor->carry)
	// {
	// 	if (VERBOSE_LVL(4))
	// 		ft_printf("zjmp %d OK\n", ((short)RAW_ARG(1)) % IDX_MOD);
	// 	move_cursor(cursor, ((short)RAW_ARG(1)) % IDX_MOD);
	// }
	// else if (VERBOSE_LVL(4))
	// 	ft_printf("zjmp %d FAILED\n", ((short)RAW_ARG(1)) % IDX_MOD);
	if (cursor->carry)
	{
		if (VERBOSE_LVL(4))
			ft_printf("P%5ld | zjmp %d OK\n", cursor->index, RAW_ARG(1) % IDX_MOD);
		move_cursor(cursor, RAW_ARG(1) % IDX_MOD);
	}
	else if (VERBOSE_LVL(4))
		ft_printf("P%5ld | zjmp %d FAILED\n", cursor->index, RAW_ARG(1) % IDX_MOD);
}

void				ldi(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;//useless
	int				addr;
	int				value[3];

	(void)argc;
	addr = cursor->position +
		(((value[0] = get_arg(entity->bg, cursor, RAW_ARG(1), arg_code(argc, 1)))) +
		((value[1] = get_arg(entity->bg, cursor, RAW_ARG(2), arg_code(argc, 2))))) % IDX_MOD;
	num = get_num_by_addr(entity->bg, addr, REG_SIZE);
	set_reg_num(cursor, (value[2] = RAW_ARG(3)), num);
	if (VERBOSE_LVL(4))
	{
		ft_printf("P%5ld | ldi %d %d r%d\n", cursor->index, value[0], value[1], value[2]);
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", value[0], value[1], value[0] + value[1], (addr));
	}

}
