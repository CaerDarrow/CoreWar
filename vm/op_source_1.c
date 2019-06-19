/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_source_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:46:26 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/19 16:32:12 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				live(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	(void)entity;(void)argc;
	cursor->last_live_call = entity->cycle;
	if (is_valid_player(entity, ARG(1)))
		entity->last_alive_player = ARG(1);
	if (VERBOSE_LVL(4))
		ft_printf("live %d\n", ARG(1));
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
	if (VERBOSE_LVL(4))
		ft_printf("ld %d r%d\n", num, ARG(2));
}

void				st(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	t_uchar			*reg_num;
	int				addr;
	int				i;

	reg_num = get_reg_num(cursor, ARG(1));
	if (arg_code(argc, 2) == REG_CODE)
	{
		set_reg_num(cursor, ARG(2), uchar_to_int(reg_num, REG_SIZE));
		if (VERBOSE_LVL(4))
			ft_printf("st r%d r%d\n", ARG(1), ARG(2));
	}
	else
	{
		addr = cursor->position + ARG(2);
		i = -1;
		while (++i < REG_SIZE)
			entity->bg[correct_position(addr + i)] = reg_num[i];
		if (VERBOSE_LVL(4))
			ft_printf("st r%d %d\n", ARG(1), ARG(2));
	}
}

void				add(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				arg[2];

	(void)entity;
	if (arg_code(argc, 1) == REG_CODE)
		arg[0] = uchar_to_int(get_reg_num(cursor, ARG(1)), REG_SIZE);
	else
		arg[0] = ARG(1);
	if (arg_code(argc, 2) == REG_CODE)
		arg[1] = uchar_to_int(get_reg_num(cursor, ARG(1)), REG_SIZE);
	else
		arg[1] = ARG(2);
	set_reg_num(cursor, ARG(3), arg[0] + arg[1]);
	set_carry(&cursor->carry, arg[0] + arg[1]);
	if (VERBOSE_LVL(4))
	{
		ft_printf("add %d", arg[0]);
		ft_printf(" %d", arg[1]);
		if (arg_code(argc, 3) == REG_CODE)
			ft_printf(" r%d\n", ARG(3));
		else
			ft_printf(" %d\n", ARG(3));
	}
}

void				sub(t_game_entity *entity, t_cursor *cursor,
						t_uchar argc, t_list *argv)
{
	int				arg[2];

	(void)entity;
	if (arg_code(argc, 1) == REG_CODE)
		arg[0] = uchar_to_int(get_reg_num(cursor, ARG(1)), REG_SIZE);
	else
		arg[0] = ARG(1);
	if (arg_code(argc, 2) == REG_CODE)
		arg[1] = uchar_to_int(get_reg_num(cursor, ARG(1)), REG_SIZE);
	else
		arg[1] = ARG(2);
	set_reg_num(cursor, ARG(3), arg[0] - arg[1]);
	set_carry(&cursor->carry, arg[0] - arg[1]);
	if (VERBOSE_LVL(4))
	{
		ft_printf("sub %d", arg[0]);
		ft_printf(" %d", arg[1]);
		if (arg_code(argc, 3) == REG_CODE)
			ft_printf(" r%d\n", ARG(3));
		else
			ft_printf(" %d\n", ARG(3));
	}
}
