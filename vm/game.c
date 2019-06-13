/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:52:41 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/13 13:52:06 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			choose_winner(t_game_entity *entity)
{
	int			i;
	t_list		*p;

	if (entity->n_players < -entity->last_alive_player || -entity->last_alive_player <= 0)//
	{
		ft_printf("No winner !\n");///
		return;
	}
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
	long long	i;

	while (entity->cursors)
	{
		if (VERBOSE_LVL(2))
			ft_printf("It is now cycle %d\n", entity->cycle);
		if (entity->cycle == 9720)
			ft_printf("BREAK\n");
		cursor_ptr = entity->cursors;
		i = 0;
		while (cursor_ptr)
		{
			cursor = (t_cursor *)cursor_ptr->data;
			if (cursor->cycles_to_exec == 0)
				set_op_code(cursor, entity->bg);
			if (cursor->cycles_to_exec > 0)
				cursor->cycles_to_exec--;
			if (cursor->cycles_to_exec == 0)
				if (is_live_op(apply_op(entity, cursor)))
					entity->live_calls++;
			cursor_ptr = cursor_ptr->next;
			i++;
		}
		check_cursors(entity);
		entity->cycle++;
	}
	choose_winner(entity);
	////
	print_bg(entity);
	ft_printf("\nGame end at %d, last alive player %d, cursors %d\n", entity->cycle - 1, -entity->last_alive_player, entity->alive_cursors);
}
