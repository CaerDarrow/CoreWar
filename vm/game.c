/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:52:41 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/15 20:32:17 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			choose_winner(t_game_entity *entity)
{
	int			i;
	t_list		*p;

	if (entity->n_players < -entity->last_alive_player || -entity->last_alive_player <= 0)//
	{
		ft_printf("No winner !\n");///
		return (-1);
	}
	p = entity->players;
	i = 0;
	while (++i < -entity->last_alive_player)
		p = p->next;
	ft_printf("Consestant %d, \"%s\", has won !\n", i,
		((t_header *)p->data)->prog_name);
	return (i);
}

int			game_loop(t_game_entity *entity)
{
	t_list		*cursor_ptr;
	t_cursor	*cursor;
	long long	i;

//	if (entity->cycle == 100)
//		return (1);
	if (entity->cursors != NULL)
	{
		if (g_d_flag == entity->cycle - 1)
		{
			print_bg(entity, 64);
			exit(0);
		}
		if (g_dump_flag == entity->cycle - 1)
		{
			print_bg(entity, 32);
			exit(0);
		}
		if (VERBOSE_LVL(2))
			ft_printf("It is now cycle %d\n", entity->cycle);
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
		go_on(entity);
		entity->cycle++;
	}
	else
		return (1);
	return (0);
}
