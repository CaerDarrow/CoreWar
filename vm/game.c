/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:52:41 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/29 21:16:42 by jjacobso         ###   ########.fr       */
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





// int				alive_players(t_game_entity *entity)
// {
// 	t_list		*c;
// 	int			alive;
//
// 	alive = 0;
// 	c = entity->cursors;
// 	while (c)
// 	{
// 		alive |= get_reg_num(c->data, 1);
// 		c = c->next;
// 	}
// 	return (BITCOUNT(alive)); /////////////////////
// }

int				time_to_apply_func(t_game_entity *entity, t_cursor *cur_cursor_data)
{
	(void)entity;(void)cur_cursor_data;
	return (1);
}

int				apply_func(t_game_entity *entity, t_cursor *cur_cursor_data)
{
	(void)entity;(void)cur_cursor_data;
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
	return (0);

}

void			kill_cursor(t_list **cur)
{
	t_list		*prev;
	t_list		*b;

	if (!*cur || !cur)
		error("Unexpected error :: kill_cursor()");
	ft_printf("Someone just died; left alive: %d\n", l_full_size(*cur));
	prev = (*cur)->prev;
	if (prev)
	{
		b = (*cur)->next;
		prev->next = b;
		destroy_cur(cur);
		*cur = prev;
		if (b)
		{
			*cur = b;
			(*cur)->prev = prev;
		}
	}
	else
	{
		b = (*cur)->next;
		destroy_cur(cur);
		*cur = b;
		if (*cur)
			(*cur)->prev = 0;
	}
}

void			try_kill_cursors(t_game_entity *entity)
{
	t_list		*cursor;
	t_list		*prev;

	prev = 0;
	cursor = entity->cursors;
	while (cursor)
	{
		if (cursor_should_die(cursor, entity->cycles_to_die))
		{
			if (prev)
				kill_cursor(&cursor);
			else
			{
				kill_cursor(&entity->cursors);
				cursor = entity->cursors;
				continue;
			}
		}
		prev = cursor;
		cursor = cursor ? cursor->next : 0;
	}
	if (entity->cursors && entity->cursors->prev)
		error("Unexpected error :: lose cursor");
}

void			check_cursors(t_game_entity *entity, int *live_calls)
{
	if (entity->cycle % entity->cycles_to_die == 0 ||
		entity->cycles_to_die <= 0)
	{
		try_kill_cursors(entity);
		if (*live_calls >= NBR_LIVE ||
			entity->cycles_with_same_ctd == MAX_CHECKS)
		{
			entity->cycles_to_die -= CYCLE_DELTA;
			entity->cycles_with_same_ctd = 0;
		}
		else
			entity->cycles_with_same_ctd++;
		*live_calls = 0;
	}
}

void			game_loop(t_game_entity *entity)
{
	(void)entity;
	t_list		*cursor;
	t_cursor	*cur_cursor_data;
	int			live_calls;
	int			func_code;

	live_calls = 0;//hide in entity
	while (l_size(entity->cursors))
	{
		cursor = entity->cursors;
		while (cursor)
		{
			cur_cursor_data = (t_cursor *)cursor->data;
			if (time_to_apply_func(entity, cur_cursor_data))
			{
				//standalone func
				func_code = apply_func(entity, cur_cursor_data);
				if (!is_valide(func_code))//validate or not after cycles?
					move_cursor(entity, cur_cursor_data);
				else if (is_live_func(func_code))
					live_calls++;
			}
			else
				shift_cycle(cur_cursor_data);
			cursor = cursor->next;
		}
		entity->cycle++;
		// ft_printf("%d\n", entity->cycle);
		check_cursors(entity, &live_calls);
	}
	//Choose winner
	// ft_printf("\nGame end %d\n", entity->cycle);
}
