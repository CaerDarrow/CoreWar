/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:24:45 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/15 20:13:08 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void					init_cursors(t_game_entity *entity)
{
	int			i;

	i = entity->n_players;
	while (i > 0)
	{
		ld_push_front(&entity->cursors, cursor_create(entity, i));
		i--;
	}
}

void					init_game_entity(t_game_entity *entity)
{
	ft_bzero(entity, sizeof(t_game_entity));
	entity->cycles_to_die = CYCLE_TO_DIE;
	g_verbose = 0;
	g_dump_flag = -1;
	g_d_flag = -1;
	entity->cycle = 1;
}

void					destroy_cursors(t_game_entity *entity)
{
	t_list				*t;
	t_list				*b;

	t = entity->cursors;
	while (t)
	{
		b = t->next;
		destroy_cur(&t);
		t = b;
	}
}

void					print_usage()
{

	ft_printf("Usage:\n\
	-v N\t: Verbosity levels, can be added together to enable several\n\
	\t* 1 : Show PC movements\n\
	\t* 2 : Show cycles\n\
	\t* 4 : Show operations\n\
	\t* 8 : Show deaths\n\
	\t* 16 : Show cursors movements\n");
}

int						main(int argc, char const *argv[])
{
	t_game_entity		entity;

	if (argc == 1)
	{
		print_usage();
		return (0);
	}
	init_game_entity(&entity);
	read_champs(argc, argv, &entity);
	init_cursors(&entity);
	init_field(&entity);
//	game_loop(&entity);
	visualizer_loop(&entity);
	ft_memdel((void **)&entity.bg);
	l_destroy(&entity.players);
	destroy_cursors(&entity);
//	gc(NULL, GC_ALL, GC_DEL);
	return (0);
}
