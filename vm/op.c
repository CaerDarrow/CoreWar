/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <zaz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/06/05 17:55:16 by jjacobso         ###   ########.fr       */
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



int					get_arg_size(unsigned char argc, int flag, int n)
{
	int				code;

	code = (argc >> (6 - (n - 1) * 2)) & 0b11;
	if (code == DIR_CODE)
	{
		// ft_printf("TYPE DIR\n");
		if (flag)
			return (DIR_SIZE);
		return (IND_SIZE);
	}
	else if (code == IND_CODE)
	{
		// ft_printf("TYPE IND\n");
		return (IND_SIZE);
	}
	else if (code == REG_CODE)
	{
		// ft_printf("TYPE REG\n");
		return (1);
	}
	return (0);
}

int					get_step(unsigned char op_code, unsigned char argc, char flag)
{
	int				i;
	int				res;

	res = 2 + g_op_tab[op_code].argtypes;
	i = -1;
	while (++i < g_op_tab[op_code].argc)
		res += get_arg_size(argc, i, flag);
	return (res);
}

// merge get arg funcs
int					get_arg1(unsigned char argc, t_list *argv, int flag)
{
	int				size;
	int				i;
	int				res;
	unsigned char	*s;

	s = (unsigned char	*)l_get_data(&argv, 1);
	size = get_arg_size(argc, flag, 1);
	res = 0;
	i = -1;
	while (++i < size)
	{
		res = (res << 8) | s[i];
	}
		// ft_printf("1:%d %s num = %d size = %d \n", res, s, get_num(s, size), size);
	return (res);
}

int					get_arg2(unsigned char argc, t_list *argv, int flag)
{
	int				size;
	int				i;
	int				res;
	unsigned char	*s;

	s = (unsigned char	*)l_get_data(&argv, 2);
	size = get_arg_size(argc, flag, 2);
	res = 0;
	i = -1;
	// s = 0x0 0xa
	while (++i < size)
		res = (res << 8) | s[i];
		// ft_printf("2:%d %s num = %d size = %d\n", res, s, get_num(s , size), size);

	return (res);
}

int					get_arg3(unsigned char argc, t_list *argv, int flag)
{
	int				size;
	int				i;
	int				res;
	unsigned char	*s;

	s = (unsigned char	*)l_get_data(&argv, 3);
	size = get_arg_size(argc, flag, 3);
	res = 0;
	i = -1;
	while (++i < size)
		res = (res << 8) | s[i];
		// ft_printf("1dddddddddd%d\n", argv[offset]);
		// ft_printf("3:%d %s num = %d size = %d\n", res, s, get_num(s, size), size);
	return (res);
}

void				live(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, t_list *argv)
{
	cursor->last_live_call = entity->cycle;
	// cursor->step = get_step(argc, argv);
	entity->last_alive_player = get_arg1(argc, argv, 1);//if not valid number = all dead?
	ft_printf("live\n");
}

void				ld(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, t_list *argv)
{
	int				num;//unsigned char *?

	(void)entity;
	set_reg_num(cursor, (num = get_arg1(argc, argv, 1)), get_arg2(argc, argv, 1));
	set_carry(&cursor->carry, num);
	ft_printf("ld\n");
}

void				st(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, t_list *argv)
{
	(void)entity;
	set_reg_num(cursor, get_arg2(argc, argv, 1), get_arg1(argc, argv, 1));
	ft_printf("st\n");
}

void				add(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, t_list *argv)
{
	int				num;

	(void)entity;
	num = get_arg1(argc, argv, 1) + get_arg2(argc, argv, 1);
	set_reg_num(cursor, get_arg3(argc, argv, 1), num);
	set_carry(&cursor->carry, num);
	ft_printf("add\n");
}

void				sub(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, t_list *argv)
{
	int				num;

	(void)entity;
	num = get_arg1(argc, argv, 1) - get_arg2(argc, argv, 1);
	set_reg_num(cursor, get_arg3(argc, argv, 1), num);
	set_carry(&cursor->carry, num);
	ft_printf("sub\n");
}

void				and(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, t_list *argv)
{
	int				num;

	(void)entity;
	num = get_arg1(argc, argv, 1) & get_arg2(argc, argv, 1);
	set_reg_num(cursor, get_arg3(argc, argv, 1), num);
	set_carry(&cursor->carry, num);
	ft_printf("and\n");
}

void				or(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, t_list *argv)
{
	int				num;

	(void)entity;
	num = get_arg1(argc, argv, 1) | get_arg2(argc, argv, 1);
	set_reg_num(cursor, get_arg3(argc, argv, 1), num);
	set_carry(&cursor->carry, num);
	ft_printf("xor\n");
}

void				xor(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, t_list *argv)
{
	int				num;

	(void)entity;
	num = XOR(get_arg1(argc, argv, 1), get_arg2(argc, argv, 1));
	set_reg_num(cursor, get_arg3(argc, argv, 1), num);
	set_carry(&cursor->carry, num);
	ft_printf("xor\n");
}

void				zjmp(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, t_list *argv)
{

	(void)entity;
	if (cursor->carry)
		move_cursor(cursor, get_arg1(argc, argv, 1));
	ft_printf("zjmp\n");
}

void				ldi(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, t_list *argv)
{
	int				num;

	(void)entity;
 	num = (get_arg1(argc, argv, 0) + get_arg2(argc, argv, 0)) % IDX_MOD;
	set_reg_num(cursor, num, get_arg2(argc, argv, 1));
	set_carry(&cursor->carry, num);
	ft_printf("ldi\n");
}

void				sti(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, t_list *argv)
{
	(void)cursor;
	(void)entity;
	// set_reg_num(cursor, get_arg1(argc, argv, 1),
	// 	(get_arg2(argc, argv, 0) + get_arg3(argc, argv, 0)) % IDX_MOD);
	entity->bg[(get_arg2(argc, argv, 0) + get_arg3(argc, argv, 0)) % IDX_MOD] = get_arg1(argc, argv, 1);
	ft_printf("sti\n");
}

void				clone(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, t_list *argv)
{
	t_cursor		*new_cursor;

	new_cursor = cursor_create(cursor->id, entity->n_players); //cursor copy
	new_cursor->reg = (unsigned char **)ft_copy_mass((void**)cursor->reg, REG_NUM);
	new_cursor->carry = cursor->carry;
	new_cursor->last_live_call = cursor->last_live_call;
	new_cursor->position = get_arg1(argc, argv, 1);
	//something more?
	ld_push_front(&entity->cursors, new_cursor);// push back?
	ft_printf("clone\n");
}

void				lld(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, t_list *argv)
{
	int				num;

	(void)entity;
	set_reg_num(cursor, (num = get_arg1(argc, argv, 0)), get_arg2(argc, argv, 0));
	set_carry(&cursor->carry, num);
}

void				lldi(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, t_list *argv)
{
	int				num;

	(void)entity;
	num = get_arg1(argc, argv, 1) + get_arg2(argc, argv, 0);
	set_reg_num(cursor, num, get_arg2(argc, argv, 1));
	set_carry(&cursor->carry, num);
	ft_printf("lldi\n");
}

void				lclone(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, t_list *argv)
{
	t_cursor		*new_cursor;

	new_cursor = cursor_create(cursor->id, entity->n_players);
	new_cursor->reg = (unsigned char **)ft_copy_mass((void**)cursor->reg, REG_NUM);
	new_cursor->carry = cursor->carry;
	new_cursor->last_live_call = cursor->last_live_call;
	new_cursor->position = get_arg1(argc, argv, 0);
	//something more?
	ld_push_front(&entity->cursors, new_cursor);// push back?
	ft_printf("lclone\n");
}

void				aff(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, t_list *argv)
{
	(void)entity;
	ft_printf("aff\n");
	ft_printf("%s\n", get_reg_num(cursor, get_arg1(argc, argv, 1)));
}

void		(*g_op_ptr[])(t_game_entity *, t_cursor *,
	unsigned char, t_list *) =
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
