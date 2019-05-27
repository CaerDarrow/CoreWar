/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:24:45 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/27 20:29:13 by jjacobso         ###   ########.fr       */
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
	l_destroy(&entity.player);
	l_destroy(&entity.cursor);
	return (0);
}
