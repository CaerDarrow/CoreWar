/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:52:41 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/10 13:35:37 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			choose_winner(t_game_entity *entity)
{
	int			i;
	t_list		*p;

	p = entity->players;
	i = 0;
	while (++i < -entity->last_alive_player)
		p = p->next;
	ft_printf("Consestant %d, \"%s\", has won !\n", i,
		((t_header *)p->data)->prog_name);
}

void			game_loop(t_game_entity *entity)
{
	t_list		*cursor_ptr;
	t_cursor	*cursor;

	while (entity->cursors)
	{
		if (g_verbose == VERBOSE_LVL(2))
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
			if (cursor->cycles_to_exec == 0)
				if (is_live_op(apply_op(entity, cursor)))
					entity->live_calls++;
			cursor_ptr = cursor_ptr->next;
		}
		check_cursors(entity);
		entity->cycle++;
	}
	choose_winner(entity);
	////
	print_bg(entity);
	ft_printf("\nGame end at %d, last alive player %d\n", entity->cycle - 1, -entity->last_alive_player);
}
