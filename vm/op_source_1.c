/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_source_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:46:26 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/10 20:28:45 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				live(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	(void)entity;(void)argc;
	cursor->last_live_call = entity->cycle;
	entity->last_alive_player = ARG(1);
}

void				ld(t_game_entity *entity, t_cursor *cursor,
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
}

void				st(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	t_uchar			*reg_num;
	int				addr;
	int				i;

	reg_num = get_reg_num(cursor, ARG(1));
	if (arg_code(argc, 2) == REG_CODE)
		set_reg_num(cursor, ARG(2), uchar_to_int(reg_num, REG_SIZE));
	else
	{
		addr = cursor->position + ARG(2);
		i = -1;
		while (++i < REG_SIZE)
			entity->bg[correct_position(addr + i)] = reg_num[i];
	}
}

void				add(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;

	(void)entity;(void)argc;
	num = ARG(1) + ARG(2);
	set_reg_num(cursor, ARG(3), num);
	set_carry(&cursor->carry, num);
}

void				sub(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;
	(void)entity;(void)argc;

	num = ARG(1) - ARG(2);
	set_reg_num(cursor, ARG(3), num);
	set_carry(&cursor->carry, num);
}
