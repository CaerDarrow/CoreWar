/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:24:45 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/05 19:08:37 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			init_cursors(t_game_entity *entity)
{
	int				i;

	i = entity->n_players;
	while (i > 0)
	{
		ld_push_front(&entity->cursors, cursor_create(entity, i));
		i--;
	}
	entity->last_alive_player = -entity->n_players;
}

static void			init_game_entity(t_game_entity *entity)
{
	ft_bzero(entity, sizeof(t_game_entity));
	entity->cycles_to_die = CYCLE_TO_DIE;
	g_verbose = 0;
	g_dump_flag = -1;
	g_d_flag = -1;
	g_n_flag = -1;
	g_free_player_num = 0;
	int_array_as_list(&g_free_player_num, 4, 1, 2, 3, 4);
	entity->cycle = 1;
}

static void			destroy_cursors(t_game_entity *entity)
{
	t_list			*t;
	t_list			*b;

	t = entity->cursors;
	while (t)
	{
		b = t->next;
		destroy_cur(entity, &t);
		t = b;
	}
}

static void			primary_entity_loop(t_game_entity *entity)
{
	while (entity->cursors != NULL)
	{
		game_loop(entity);
		entity->cycle++;
	}
	choose_winner(entity);
}

int					main(int argc, char const *argv[])
{
	t_game_entity	entity;

	if (argc == 1)
	{
		print_usage();
		return (0);
	}
	init_game_entity(&entity);
	read_champs(argc, argv, &entity);
	l_destroy(&g_free_player_num);
	init_cursors(&entity);
	if (entity.vis_key != 0)
	{
		init_field(&entity);
		visualizer_loop(&entity);
	}
	else
	{
		primary_entity_loop(&entity);
	}
	ft_memdel((void **)&entity.bg);
	destroy_cursors(&entity);
	return (0);
}
