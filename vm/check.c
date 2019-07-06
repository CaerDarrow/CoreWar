/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:37:52 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/06 17:20:05 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		kill_cursor(t_game_entity *entity, t_list **cur)
{
	t_list		*prev;
	t_list		*b;

	prev = (*cur)->prev;
	if (prev)
	{
		b = (*cur)->next;
		prev->next = b;
		destroy_cur(entity, cur);
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
		destroy_cur(entity, cur);
		*cur = b;
		if (*cur)
			(*cur)->prev = 0;
	}
}

static void		cursor_debug_info(t_game_entity *entity, t_cursor *cursor)
{
	if (VERBOSE_LVL(8))
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
			cursor->index, entity->cycle -
			cursor->last_live_call, entity->cycles_to_die);
}

static void		try_kill_cursors(t_game_entity *entity)
{
	t_list		*cursor;
	t_list		*prev;

	prev = 0;
	cursor = entity->cursors;
	while (cursor)
	{
		if (cursor_should_die(CURSOR(cursor), entity))
		{
			if (!prev)
			{
				cursor_debug_info(entity, CURSOR(cursor));
				kill_cursor(entity, &entity->cursors);
				cursor = entity->cursors;
				continue;
			}
			cursor_debug_info(entity, CURSOR(cursor));
			kill_cursor(entity, &cursor);
			cursor = cursor->prev;
		}
		prev = cursor;
		cursor = cursor ? cursor->next : 0;
	}
}

void			check_cursors(t_game_entity *entity)
{
	if (entity->cycle - entity->last_check >= entity->cycles_to_die ||
		entity->cycles_to_die <= 0)
	{
		try_kill_cursors(entity);
		entity->periods_with_same_ctd++;
		if (entity->live_calls >= NBR_LIVE ||
			entity->periods_with_same_ctd == MAX_CHECKS)
		{
			entity->cycles_to_die -= CYCLE_DELTA;
			entity->periods_with_same_ctd = 0;
			if (VERBOSE_LVL(2))
				ft_printf("Cycle to die is now %d\n", entity->cycles_to_die);
		}
		entity->live_calls = 0;
		entity->last_check = entity->cycle;
	}
}
