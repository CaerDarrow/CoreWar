/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <zaz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/05/31 19:39:48 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_op	g_op_tab[] =
{
	{0, 0, (int []){0}, 0, 0, 0, 0, 0},
	{"live", 1, (int []){T_DIR}, 1, 10, "alive", 0, 1},
	{"ld", 2, (int []){T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 1},
	{"st", 2, (int []){T_REG, T_IND | T_REG}, 3, 5, "store", 1, 1},
	{"add", 3, (int []){T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 1},
	{"sub", 3, (int []){T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 1},
	{"and", 3, (int []){T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 1},
	{"or", 3, (int []){T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 1},
	{"xor", 3, (int []){T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 1},
	{"zjmp", 1, (int []){T_DIR}, 9, 20, "jump if zero", 0, 0},
	{"ldi", 3, (int []){T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 0},
	{"sti", 3, (int []){T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 0},
	{"clone", 1, (int []){T_DIR}, 12, 800, "clone", 0, 0},
	{"lld", 2, (int []){T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 1},
	{"lldi", 3, (int []){T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 0},
	{"lclone", 1, (int []){T_DIR}, 15, 1000, "long clone", 0, 2},
	{"aff", 1, (int []){T_REG}, 16, 2, "aff", 1, 1},
};


void				set_carry(char *carry, int num)
{
	if (num == 0)
		*carry = 1;
	else
		*carry = 0;
}

char				type(char argc, char flag)
{
	return (argc & flag);
}

char				get_step(unsigned char argc, unsigned char *argv)
{
	(void)argv;
	(void)argc;
	return (6);
}

int					get_arg1(unsigned char argc, unsigned char *argv, int flag)
{
	(void)argv;
	(void)argc;
	(void)flag;

	return (-1);
}

int					get_arg2(unsigned char argc, unsigned char *argv, int flag)
{
	(void)argv;
	(void)argc;
	(void)flag;

	return (-1);
}

int					get_arg3(unsigned char argc, unsigned char *argv, int flag)
{
	(void)argv;
	(void)argc;
	(void)flag;

	return (-1);
}

void				live(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	cursor->last_live_call = entity->cycle;
	cursor->step = get_step(argc, argv);
	entity->last_alive_player = get_arg1(argc, argv, 1);//if not valide number = all dead?
}

void				ld(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	int				num;

	(void)entity;
	// read T_REG_SIZE BYTES; T_REG is machine word
	set_reg_num(cursor, (num = get_arg1(argc, argv, 1)), get_arg2(argc, argv, 1));
	set_carry(&cursor->carry, num);
}

void				st(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	(void)entity;
	set_reg_num(cursor, get_arg2(argc, argv, 1), get_arg1(argc, argv, 1));
}

void				add(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	int				num;

	(void)entity;
	num = get_arg1(argc, argv, 1) + get_arg2(argc, argv, 1);
	set_reg_num(cursor, get_arg3(argc, argv, 1), num);
	set_carry(&cursor->carry, num);
}

void				sub(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	int				num;

	(void)entity;
	num = get_arg1(argc, argv, 1) - get_arg2(argc, argv, 1);
	set_reg_num(cursor, get_arg3(argc, argv, 1), num);
	set_carry(&cursor->carry, num);
}

void				and(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	int				num;

	(void)entity;
	num = get_arg1(argc, argv, 1) & get_arg2(argc, argv, 1);
	set_reg_num(cursor, get_arg3(argc, argv, 1), num);
	set_carry(&cursor->carry, num);
}

void				or(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	int				num;

	(void)entity;
	num = get_arg1(argc, argv, 1) | get_arg2(argc, argv, 1);
	set_reg_num(cursor, get_arg3(argc, argv, 1), num);
	set_carry(&cursor->carry, num);
}

void				xor(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	int				num;

	(void)entity;
	num = XOR(get_arg1(argc, argv, 1), get_arg2(argc, argv, 1));
	set_reg_num(cursor, get_arg3(argc, argv, 1), num);
	set_carry(&cursor->carry, num);
}

void				zjmp(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{

	(void)entity;
	if (cursor->carry)
		move_cursor(cursor, get_arg1(argc, argv, 1));
}

void				ldi(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	int				num;

	(void)entity;
 	num = (get_arg1(argc, argv, 1) + get_arg2(argc, argv, 1)) % IDX_MOD;
	set_reg_num(cursor, num, get_arg2(argc, argv, 1));
	set_carry(&cursor->carry, num);
}

void				sti(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{

	(void)entity;
	set_reg_num(cursor, get_arg3(argc, argv, 1),
		(get_arg1(argc, argv, 1) + get_arg2(argc, argv, 1)) % IDX_MOD);
}

void				clone(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	t_cursor		*new_cursor;

	new_cursor = cursor_create(cursor->id, entity->n_players); //cursor copy
	new_cursor->reg = (unsigned char **)ft_copy_mass((void**)cursor->reg, REG_NUM);
	new_cursor->carry = cursor->carry;
	new_cursor->last_live_call = cursor->last_live_call;
	new_cursor->position = get_arg1(argc, argv, 1);
	//something more?
	ld_push_front(&entity->cursors, new_cursor);// push back?
}

void				lld(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	int				num;

	(void)entity;
	set_reg_num(cursor, (num = get_arg1(argc, argv, 0)), get_arg2(argc, argv, 0));
	set_carry(&cursor->carry, num);
}

void				lldi(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	int				num;

	(void)entity;
	num = get_arg1(argc, argv, 1) + get_arg2(argc, argv, 1);
	set_reg_num(cursor, num, get_arg2(argc, argv, 1));
	set_carry(&cursor->carry, num);

}

void				lclone(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	t_cursor		*new_cursor;

	new_cursor = cursor_create(cursor->id, entity->n_players);
	new_cursor->reg = (unsigned char **)ft_copy_mass((void**)cursor->reg, REG_NUM);
	new_cursor->carry = cursor->carry;
	new_cursor->last_live_call = cursor->last_live_call;
	new_cursor->position = get_arg1(argc, argv, 0);
	//something more?
	ld_push_front(&entity->cursors, new_cursor);// push back?

}

void				aff(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	(void)entity;
	ft_printf("c\n", get_reg_num(cursor, get_arg1(argc, argv, 1)));
}

void		(*g_op_ptr[])(t_game_entity *, t_cursor *,
	unsigned char, unsigned char *) =
{
	NULL,
	&live,
	&ld,
	&st,
	&add,
	&sub,
	&and,
	&or,
	&xor,
	&zjmp,
	&ldi,
	&sti,
	&clone,
	&lld,
	&lldi,
	&lclone,
	&aff,
};
