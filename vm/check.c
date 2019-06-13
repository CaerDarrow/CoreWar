/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:37:52 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/13 13:34:03 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "vm.h"

 static void	kill_cursor(t_list **cur)
 {
 	t_list		*prev;
 	t_list		*b;

 	if (!cur || !*cur)
 		error("Unexpected error :: kill_cursor()");
	// ft_printf("Someone just died(player's %d cursor); left alive: %d\n", l_full_size(*cur), ((t_cursor *)(*cur)->data)->id);
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
	// t_cursor	*c;

 	prev = 0;
 	cursor = entity->cursors;
 	while (cursor)
 	{
 		if (cursor_should_die(cursor, entity))
 		{
 			if (prev)
 			{
				if (VERBOSE_LVL(8))
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",CURSOR(cursor)->index, entity->cycle - CURSOR(cursor)->last_live_call, entity->cycles_to_die );
 				kill_cursor(&cursor);
				cursor = cursor->prev;/////////////////////////////////!!!!!!!!!!!!!!
				// entity->alive_cursors--;
				// ft_printf("\tF\n");
 			}
 			else
 			{
				if (VERBOSE_LVL(8))
 					ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",CURSOR(entity->cursors)->index, entity->cycle - CURSOR(entity->cursors)->last_live_call, entity->cycles_to_die );
 				kill_cursor(&entity->cursors);
				// ft_printf("\tF\n");
				// entity->alive_cursors--;
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
 	if (entity->cycle - entity->last_check >= entity->cycles_to_die ||
 		entity->cycles_to_die <= 0)
 	{
 		try_kill_cursors(entity);
		entity->periods_with_same_ctd++;///////?
		// if (entity->last_check != 0)
		// {
	 		if (entity->live_calls >= NBR_LIVE ||
	 			entity->periods_with_same_ctd == MAX_CHECKS)
	 		{
	 			entity->cycles_to_die -= CYCLE_DELTA;
	 			entity->periods_with_same_ctd = 0;
	 		}
		// }
 		entity->live_calls = 0;
		if (VERBOSE_LVL(2))
			ft_printf("Cycle to die is now %d\n", entity->cycles_to_die);
		entity->last_check = entity->cycle;
 	}
 }
