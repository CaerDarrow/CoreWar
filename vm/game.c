/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:52:41 by jjacobso          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/07/06 17:09:27 by jjacobso         ###   ########.fr       */
=======
/*   Updated: 2019/07/06 16:52:08 by jjacobso         ###   ########.fr       */
>>>>>>> 7a00320bd65b65add1570375e7def3d4d2a0b9c4
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				choose_winner(t_game_entity *entity)
{
	int			i;

	if (ft_inrange(-entity->last_alive_player, 1, entity->n_players))
		i = -entity->last_alive_player;
	else
		i = 1;
	PRINT("Contestant %d, \"%s\", has won !\n", i,
		entity->players[i - 1].prog_name);
	return (i);
}

static void		game_loop_debug(t_game_entity *entity)
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
		PRINT("It is now cycle %d\n", entity->cycle);
}

int				game_loop(t_game_entity *entity)
{
	t_list		*cursor_ptr;
	t_cursor	*cursor;
	long long	i;
<<<<<<< HEAD
	// int buff;
	game_loop_debug(entity);
	cursor_ptr = entity->cursors;
	i = 0;
	// if (entity->cycle == 15930)
	// 	{
	//
	// 	}
	while (cursor_ptr)
	{
		cursor = (t_cursor *)cursor_ptr->data;
		// if (cursor->position == 0x0faa)
		// 	{
		// 		buff = cursor->cycles_to_exec;
		// 	}
=======
	int buff;
	game_loop_debug(entity);
	cursor_ptr = entity->cursors;
	i = 0;
	if (entity->cycle == 15930)
		{

		}
	while (cursor_ptr)
	{
		cursor = (t_cursor *)cursor_ptr->data;
		if (cursor->position == 0x0faa)
			{
				buff = cursor->cycles_to_exec;
			}
>>>>>>> 7a00320bd65b65add1570375e7def3d4d2a0b9c4
		if (cursor->cycles_to_exec == 0)
			set_op_code(cursor, entity->bg);
		if (cursor->cycles_to_exec > 0)
			cursor->cycles_to_exec--;
		if (cursor->cycles_to_exec == 0 && apply_op(entity, cursor) == 1)
			entity->live_calls++;
		cursor_ptr = cursor_ptr->next;
		i++;
	}
	check_cursors(entity);
	return (0);
}
