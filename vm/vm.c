/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:24:45 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/05 18:32:34 by jjacobso         ###   ########.fr       */
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

static void			print_usage(void)
{
	ft_printf("Usage:\n"
	"\t-a\t: Prints output from \"aff\" (Default is to hide it)\n"
	"#### TEXT OUTPUT MODE ##################################################\n"
	"\t-d N\t: Dumps memory (x64 mode) after N cycles then exits\n"
	"\t-dump N\t: Dumps memory (x32 mode) after N cycles then exits\n"
	"\t-n N\t: Sets the number of the next player\n"
	"\t-v N\t: Verbosity levels, can be added together to enable several\n"
	"\t\t* 2 : Show cycles\n"
	"\t\t* 4 : Show operations\n"
	"\t\t* 8 : Show deaths\n"
	"\t\t* 16 : Show cursors movements\n"
	"#### OUTPUT MODE #######################################################\n"
	"\t-vis N\t: Turn on visualisator and/or set size of cell\n"
	"\t\t* N in range [1, 18] or not defined; (18 is warcraft mode)\n");
}

int					main(int argc, char const *argv[])
{
	t_game_entity		entity;


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
		while (entity.cursors != NULL)
		{
			game_loop(&entity);
			entity.cycle++;
		}
		choose_winner(&entity);
	}
	ft_memdel((void **)&entity.bg);
	destroy_cursors(&entity);
	return (0);
}
