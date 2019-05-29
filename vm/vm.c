/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:24:45 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/29 21:12:35 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void					init_cursors(t_game_entity *entity)
{
	int			i;

	i = entity->n_players;
	ft_printf("%d\n", i);
	while (i > 0)
	{
		ld_push_front(&entity->cursors, cursor_create(i));
		i--;
	}
}

void					init_game_entity(t_game_entity *entity)
{
	ft_bzero(entity, sizeof(t_game_entity));
	entity->cycles_to_die = CYCLE_TO_DIE;
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

int						main(int argc, char const *argv[])
{
	t_game_entity		entity;

	if (argc == 1)
		return (ft_printf("Usage:\n"));
	init_game_entity(&entity);
	read_champs(argc, argv, &entity);
	init_cursors(&entity);
	game_loop(&entity);
	ft_memdel((void **)&entity.bg);
	l_destroy(&entity.players);
	destroy_cursors(&entity);
	return (0);
}
