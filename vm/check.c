/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:37:52 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/07 20:55:11 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "vm.h"

 static void	kill_cursor(t_list **cur)
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

 static void	try_kill_cursors(t_game_entity *entity)
 {
 	t_list		*cursor;
 	t_list		*prev;

 	prev = 0;
 	cursor = entity->cursors;
 	while (cursor)
 	{
 		if (cursor_should_die(cursor, entity))
 		{
 			if (prev)
 			{
 				ft_printf("Cursor died; cycles_to_die: %d\n", entity->cycles_to_die );
 				kill_cursor(&cursor);
 			}
 			else
 			{
 				ft_printf("Cursor died; cycles_to_die: %d\n", entity->cycles_to_die );
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


 void			check_cursors(t_game_entity *entity)
 {
 	if (entity->cycle % entity->cycles_to_die == 0 ||
 		entity->cycles_to_die <= 0)
 	{
 		try_kill_cursors(entity);
 		if (entity->live_calls >= NBR_LIVE ||
 			entity->cycles_with_same_ctd == MAX_CHECKS)
 		{
 			entity->cycles_to_die -= CYCLE_DELTA;
 			entity->cycles_with_same_ctd = 0;
 		}
 		else
 			entity->cycles_with_same_ctd++;
 		entity->live_calls = 0;
 	}
 }
