/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <zaz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/07/04 19:24:27 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_op	g_op_tab[] =
{
	{0, 0, (char[]){0}, 0, 0, 0, 0, 0},
	{"live", 1, (char[]){T_DIR}, 1, 10, &live, 0, 1},
	{"ld", 2, (char[]){T_DIR | T_IND, T_REG}, 2, 5, &ld, 1, 1},
	{"st", 2, (char[]){T_REG, T_IND | T_REG}, 3, 5, &st, 1, 1},
	{"add", 3, (char[]){T_REG, T_REG, T_REG}, 4, 10, &add, 1, 1},
	{"sub", 3, (char[]){T_REG, T_REG, T_REG}, 5, 10, &sub, 1, 1},
	{"and", 3, (char[]){T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6,
		6, &and, 1, 1},
	{"or", 3, (char[]){T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7,
		6, &or, 1, 1},
	{"xor", 3, (char[]){T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8,
		6, &xor, 1, 1},
	{"zjmp", 1, (char[]){T_DIR}, 9, 20, &zjmp, 0, 0},
	{"ldi", 3, (char[]){T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		&ldi, 1, 0},
	{"sti", 3, (char[]){T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		&sti, 1, 0},
	{"fork", 1, (char[]){T_DIR}, 12, 800, &clone, 0, 0},
	{"lld", 2, (char[]){T_DIR | T_IND, T_REG}, 13, 10, &lld, 1, 1},
	{"lldi", 3, (char[]){T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		&lldi, 1, 0},
	{"lfork", 1, (char[]){T_DIR}, 15, 1000, &lclone, 0, 0},
	{"aff", 1, (char[]){T_REG}, 16, 2, &aff, 1, 1},
};
