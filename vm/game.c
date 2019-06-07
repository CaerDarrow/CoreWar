/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:52:41 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/07 19:40:22 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			game_loop(t_game_entity *entity)
{
	t_list		*cursor_ptr;
	t_cursor	*cursor;

	while (entity->cursors)
	{
		if (g_verbose)
			ft_printf("It is now cycle %d\n", entity->cycle);
		if (entity->cycle == 1535)
			ft_printf("BREAK\n");
		cursor_ptr = entity->cursors;
		while (cursor_ptr)
		{
			cursor = (t_cursor *)cursor_ptr->data;
			if (cursor->moved)
				set_op_code(cursor, entity->bg);
			if (cursor->cycles_to_exec > 0)
				cursor->cycles_to_exec--;
			else if (cursor->cycles_to_exec == 0)
				if (is_live_op(apply_op(entity, cursor)))
					entity->live_calls++;
			cursor_ptr = cursor_ptr->next;
		}
		entity->cycle++;
		check_cursors(entity);
	}
	print_bg(entity);
	//Choose winner
	ft_printf("\nGame end at %d, last alive player %d\n", entity->cycle , -entity->last_alive_player);
}
