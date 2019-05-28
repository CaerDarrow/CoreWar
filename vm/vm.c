/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:24:45 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/28 15:46:28 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int						main(int argc, char const *argv[])
{
	t_game_entity		entity;


	if (argc == 1)
		return (ft_printf("Usage:\n"));
	read_champs(argc, argv, &entity);
	game_loop(&entity);
	ft_memdel((void **)&entity.bg);
	l_destroy(&entity.players);
	l_destroy(&entity.cursors);
	return (0);
}
