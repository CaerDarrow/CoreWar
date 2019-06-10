/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_source_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:47:50 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/10 14:22:54 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				and(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;

	(void)entity;
	num = get_arg(argc, argv, 1, 1) & get_arg(argc, argv, 2, 1);
	set_reg_num(cursor, get_arg(argc, argv, 3, 1), num);
	set_carry(&cursor->carry, num);
}

void				or(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;

	(void)entity;
	num = get_arg(argc, argv, 1, 1) | get_arg(argc, argv, 2, 1);
	set_reg_num(cursor, get_arg(argc, argv, 3, 1), num);
	set_carry(&cursor->carry, num);
}

void				xor(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;

	(void)entity;
	num = XOR(get_arg(argc, argv, 1, 1), get_arg(argc, argv, 2, 1));
	set_reg_num(cursor, get_arg(argc, argv, 3, 1), num);
	set_carry(&cursor->carry, num);
}

void				zjmp(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{

	(void)entity;
	if (cursor->carry)
		move_cursor(cursor, get_arg(argc, argv, 1, g_op_tab[cursor->op_code].t_dirsize));
	if (g_verbose > 0)
		ft_printf("Player's cursor %d at %d; arg: %d\n", cursor->id, cursor->position, get_arg(argc, argv, 1, g_op_tab[cursor->op_code].t_dirsize));
}

void				ldi(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				num;

	(void)entity;
 	num = (get_arg(argc, argv, 1, 0) + get_arg(argc, argv, 2, 0)) % IDX_MOD;
	set_reg_num(cursor, num, get_arg(argc, argv, 2, 1));
	set_carry(&cursor->carry, num);
}
