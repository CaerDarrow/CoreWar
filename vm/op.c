/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <zaz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/05/31 16:22:44 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_op	g_op_tab[] =
{
	{0, 0, (int []){0}, 0, 0, 0, 0, 0},
	{"live", 1, (int []){T_DIR}, 1, 10, "alive", 0, 4},
	{"ld", 2, (int []){T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 4},
	{"st", 2, (int []){T_REG, T_IND | T_REG}, 3, 5, "store", 1, 4},
	{"add", 3, (int []){T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 4},
	{"sub", 3, (int []){T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 4},
	{"and", 3, (int []){T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 4},
	{"or", 3, (int []){T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 4},
	{"xor", 3, (int []){T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 4},
	{"zjmp", 1, (int []){T_DIR}, 9, 20, "jump if zero", 0, 2},
	{"ldi", 3, (int []){T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 2},
	{"sti", 3, (int []){T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 2},
	{"clone", 1, (int []){T_DIR}, 12, 800, "clone", 0, 2},
	{"lld", 2, (int []){T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 4},
	{"lldi", 3, (int []){T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 2},
	{"lclone", 1, (int []){T_DIR}, 15, 1000, "long clone", 0, 2},
	{"aff", 1, (int []){T_REG}, 16, 2, "aff", 1, 4},
};


void				set_carry(char *carry, int num)
{
	if (num == 0)
		*carry = 1;
	else
		*carry = 0;
}

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

int					get_arg2(unsigned char argc, unsigned char *argv)
{
	(void)argv;
	(void)argc;
	return (-1);
}

int					get_arg3(unsigned char argc, unsigned char *argv)
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

void				ld(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	(void)entity;(void)cursor;(void)argc;(void)argv;
	int				num;

	// read T_REG_SIZE BYTES; T_REG is machine word
	set_reg_num(cursor, (num = get_arg1(argc, argv)), get_arg2(argc, argv));
	set_carry(&cursor->carry, num);
}

void				st(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	(void)entity;(void)cursor;(void)argc;(void)argv;
}

void				add(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	(void)entity;(void)cursor;(void)argc;(void)argv;

}

void				sub(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	(void)entity;(void)cursor;(void)argc;(void)argv;

}

void				and(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	(void)entity;(void)cursor;(void)argc;(void)argv;

}

void				or(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	(void)entity;(void)cursor;(void)argc;(void)argv;

}

void				xor(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	(void)entity;(void)cursor;(void)argc;(void)argv;

}

void				zjmp(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	(void)entity;(void)cursor;(void)argc;(void)argv;

}

void				ldi(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	(void)entity;(void)cursor;(void)argc;(void)argv;

}

void				sti(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	(void)entity;(void)cursor;(void)argc;(void)argv;

}

void				clone(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	(void)entity;(void)cursor;(void)argc;(void)argv;

}

void				lld(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	(void)entity;(void)cursor;(void)argc;(void)argv;

}

void				lldi(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	(void)entity;(void)cursor;(void)argc;(void)argv;

}

void				lclone(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	(void)entity;(void)cursor;(void)argc;(void)argv;

}

void				aff(t_game_entity *entity, t_cursor *cursor,
						unsigned char argc, unsigned char *argv)
{
	(void)entity;(void)cursor;(void)argc;(void)argv;

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
