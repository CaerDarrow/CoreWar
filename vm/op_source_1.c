/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_source_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:46:26 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/04 19:14:46 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				live(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	cursor->last_live_call = entity->cycle;
	if (is_valid_player(entity, RAW_ARG(1)))
		entity->last_alive_player = RAW_ARG(1);
	if (VERBOSE_LVL(4))
		ft_printf("P%5ld | live %d\n", cursor->index, RAW_ARG(1));
}

void				ld(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				b[2];

	b[0] = get_arg(entity->bg, cursor, RAW_ARG(1), arg_code(argc, 1));
	b[1] = RAW_ARG(2);
	set_reg_num(cursor, b[1], b[0]);
	set_carry(&cursor->carry, b[0]);
	if (VERBOSE_LVL(4))
		ft_printf("P%5ld | ld %d r%d\n", cursor->index, b[0], b[1]);
}

void				st(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	t_uchar			*reg_num;
	int				addr;
	int				i;
	int				b[2];

	reg_num = get_reg_num(cursor,
			b[0] = RAW_ARG(1));
	if (arg_code(argc, 2) == REG_CODE)
		set_reg_num(cursor, (b[1] = RAW_ARG(2)),
				uchar_to_int(reg_num, REG_SIZE));
	else
	{
		addr = cursor->position +
			(b[1] = RAW_ARG(2)) % IDX_MOD;
		i = -1;
		while (++i < REG_SIZE)
		{
			entity->vis_key ? entity->SQ->num_sq = correct_position(addr + i)
					: 0;
			entity->bg[correct_position(addr + i)] = reg_num[i];
			entity->vis_key ? draw_square(entity->vis, cursor->id - 1) : 0;
		}
	}
	if (VERBOSE_LVL(4))
		ft_printf("P%5ld | st r%d %d\n", cursor->index, b[0], b[1]);
}

void				add(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				b[3];
	int				res;

	(void)entity;
	res =
		uchar_to_int(get_reg_num(cursor, (b[0] = RAW_ARG(1))), REG_SIZE) +
		uchar_to_int(get_reg_num(cursor, (b[1] = RAW_ARG(2))), REG_SIZE);
	set_reg_num(cursor, (b[2] = RAW_ARG(3)), res);
	set_carry(&cursor->carry, res);
	if (VERBOSE_LVL(4))
	{
		ft_printf("P%5ld | add r%d r%d r%d\n", cursor->index, b[0],
			b[1], b[2]);
	}
}

void				sub(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				b[3];
	int				res;

	(void)entity;
	res =
		uchar_to_int(get_reg_num(cursor, (b[0] = RAW_ARG(1))), REG_SIZE) -
		uchar_to_int(get_reg_num(cursor, (b[1] = RAW_ARG(2))), REG_SIZE);
	set_reg_num(cursor, (b[2] = RAW_ARG(3)), res);
	set_carry(&cursor->carry, res);
	if (VERBOSE_LVL(4))
	{
		ft_printf("P%5ld | sub r%d r%d r%d\n", cursor->index, b[0],
			b[1], b[2]);
	}
}
