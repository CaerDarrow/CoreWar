/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:52:41 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/28 20:00:39 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			print_bg(t_game_entity *entity)
{
	int			i;
	i = -1;
	while (++i < MEM_SIZE)
	{
		ft_printf("%02x ", entity->bg[i]);
		if (i % 64 == 63)
			ft_printf("\n");
	}
}

void			set_reg_num(t_cursor *c, int n, int value)//only less or eq to u32
{
	(void)c;(void)n;(void)value;
}

int				get_reg_num(t_cursor *c, int n)//only less or eq to u32
{
	(void)c;(void)n;
	return (n);
}

t_cursor		*cursor_create(int id)
{
	t_cursor	*c;
	int			i;

	if (!(c = (t_cursor *)malloc(sizeof(t_cursor))))
		error("Malloc error");
	ft_bzero(c, sizeof(t_cursor));
	if (!(c->reg = (char **)malloc(16 * sizeof(char *))))
		error("Malloc error");
	i = -1;
	while (++i < 16)
	{
		if (!(c->reg[i] = malloc(REG_SIZE)))
			error("Malloc error");
		ft_bzero(c->reg[i], REG_SIZE);
		set_reg_num(c, 1, id);
	}
	return (c);
}

void			init_cursors(t_game_entity *entity)
{
	int			i;

	i = entity->n_players;
	while (i > 0)
	{
		ld_push_front(&entity->cursors, cursor_create(i));
		i--;
	}
}



int				alive_players(t_game_entity *entity)
{
	t_list		*c;
	int			alive;

	alive = 0;
	c = entity->cursors;
	while (c)
	{
		alive |= get_reg_num(c->data, 1);
		c = c->next;
	}
	return (BITCOUNT(alive)); /////////////////////
}

int				time_to_apply_func(t_game_entity *entity, t_cursor *cur_cursor)
{
	(void)entity;(void)cur_cursor;
	return (1);
}

int				apply_func(t_game_entity *entity, t_cursor *cur_cursor)
{
	(void)entity;(void)cur_cursor;
	return (1);

}

int				is_valide(int func_code)
{
	(void)func_code;
	return (1);

}

int				is_live_func(int func_code)
{
	(void)func_code;
	return (1);

}

void			move_cursor(t_game_entity *entity, t_cursor *cur_cursor)
{
	(void)entity;(void)cur_cursor;

}

void			shift_cycle(t_cursor *cur_cursor)
{
	cur_cursor->cycles_to_exec--;
	if (cur_cursor->cycles_to_exec < 0)///
		error("Something bad happened");///
}

int				check_cursors(t_game_entity *entity, int *live_calls)
{
	// adjust_cycles_to_die(entity, live_calls);
	// check_cursors(entity);
	// if (entity->cycle % entity->cycles_to_die == 0 ||
	// 	entity->cycles_to_die <= 0)
	// {
	// 	live_calls = 0;
	// }
	(void)live_calls;
	if (alive_players(entity) <= 1)
		return (0);
	return (1);
}

void			game_loop(t_game_entity *entity)
{
	t_list		*cursor;
	t_cursor	*cur_cursor;
	int			live_calls;
	int			func_code;

	init_cursors(entity);
	live_calls = 0;//hide in entity
	while (1)
	{
		cursor = entity->cursors;
		while (cursor)
		{
			cur_cursor = (t_cursor *)cursor->data;
			if (time_to_apply_func(entity, cur_cursor))
			{
				//standalone func
				func_code = apply_func(entity, cur_cursor);
				if (!is_valide(func_code))//validate or not after cycles?
					move_cursor(entity, cur_cursor);
				else if (is_live_func(func_code))
					live_calls++;
			}
			else
				shift_cycle(cur_cursor);
			cursor = cursor->next;
		}
		entity->cycle++;
		if (!check_cursors(entity, &live_calls))
			break ;
	}
}
