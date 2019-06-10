/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_source_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:46:26 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/10 16:44:21 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				live(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	cursor->last_live_call = entity->cycle;
	// cursor->step = get_step(argc, argv);
	entity->last_alive_player = get_arg(argc, argv, 1, 1);//if not valid number = all dead?
}

void				ld(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;//t_uchar *?

	(void)entity;
	set_reg_num(cursor, get_arg(argc, argv, 2, 1), (num = get_arg(argc, argv, 1, 1)));
	set_carry(&cursor->carry, num);
}

void				st(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	t_uchar			*reg_num;
	int				addr;
	int				i;

	//set reg if 2 argc is reg
	reg_num = get_reg_num(cursor, get_arg(argc, argv, 1, g_op_tab[cursor->op_code].t_dirsize));
	if (arg_type(argc, 2) == REG_CODE)
	{
		set_reg_num(cursor, get_arg(argc, argv, 2, g_op_tab[cursor->op_code].t_dirsize), uchar_to_int(reg_num, REG_SIZE));
	}
	else
	{
		addr = (cursor->position + get_arg(argc, argv, 2, g_op_tab[cursor->op_code].t_dirsize)) % IDX_MOD;
		i = -1;
		while (++i < REG_SIZE)
			entity->bg[correct_position(addr + i)] = reg_num[i];
	}
}

void				add(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;

	(void)entity;
	num = get_arg(argc, argv, 1, 1) + get_arg(argc, argv, 2, 1);
	set_reg_num(cursor, get_arg(argc, argv, 3, 1), num);
	set_carry(&cursor->carry, num);
}

void				sub(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;

	(void)entity;
	num = get_arg(argc, argv, 1, 1) - get_arg(argc, argv, 2, 1);
	set_reg_num(cursor, get_arg(argc, argv, 3, 1), num);
	set_carry(&cursor->carry, num);
}
