/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_source_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:48:20 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/10 14:42:40 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				sti(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	t_uchar			*reg_num;
	int				addr;
	int				i;

	addr = (cursor->position + get_arg(argc, argv, 2, 0) + get_arg(argc, argv, 3, 0)) % IDX_MOD;
	reg_num = get_reg_num(cursor, get_arg(argc, argv, 1, 1));
	i = -1;
	while (++i < REG_SIZE)
		entity->bg[addr + i] = reg_num[i];
}

void				clone(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	t_cursor		*new_cursor;

	new_cursor = cursor_create(cursor->id, entity->n_players); //cursor copy
	new_cursor->reg = (t_uchar **)ft_copy_mass((void**)cursor->reg, REG_NUM);
	new_cursor->carry = cursor->carry;
	new_cursor->last_live_call = cursor->last_live_call;
	new_cursor->position = get_arg(argc, argv, 1, 1);
	//something more?
	ld_push_front(&entity->cursors, new_cursor);// push back?
}

void				lld(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;

	(void)entity;
	set_reg_num(cursor, (num = get_arg(argc, argv, 1, 0)), get_arg(argc, argv, 2, 0));
	set_carry(&cursor->carry, num);
}

void				lldi(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;

	(void)entity;
	num = get_arg(argc, argv, 1, 1) + get_arg(argc, argv, 2, 0);
	set_reg_num(cursor, num, get_arg(argc, argv, 3, 1));
	set_carry(&cursor->carry, num);
}

void				lclone(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	t_cursor		*new_cursor;

	new_cursor = cursor_create(cursor->id, entity->n_players);
	new_cursor->reg = (t_uchar **)ft_copy_mass((void**)cursor->reg, REG_NUM);
	new_cursor->carry = cursor->carry;
	new_cursor->last_live_call = cursor->last_live_call;
	new_cursor->position = get_arg(argc, argv, 1, 0);
	//something more?
	ld_push_front(&entity->cursors, new_cursor);// push back?
}
