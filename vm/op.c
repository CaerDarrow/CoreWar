/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <zaz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/05/31 14:17:19 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_op	g_op_tab[] =
{
	{0, 0, (int []){0}, 0, 0, 0, 0, 0},
	{"live", 1, (int []){T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, (int []){T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, (int []){T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, (int []){T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, (int []){T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, (int []){T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, (int []){T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, (int []){T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, (int []){T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, (int []){T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, (int []){T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, (int []){T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, (int []){T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, (int []){T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, (int []){T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, (int []){T_REG}, 16, 2, "aff", 1, 0},
};

char				get_step(unsigned char argc, unsigned char *argv)
{
	(void)argv;
	(void)argc;
	return (6);
}

int					get_arg1(unsigned char argc, unsigned char *argv)
{
	(void)argv;
	(void)argc;
	return (-1);
}

void				live(t_game_entity *entity, t_cursor *cursor,
unsigned char argc, unsigned char *argv)
{
	cursor->last_live_call = entity->cycle;
	cursor->step = get_step(argc, argv);
	entity->last_alive_player = get_arg1(argc ,argv);//if not valide number = all dead?
}
