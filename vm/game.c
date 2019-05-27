/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:52:41 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/27 20:24:33 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			game_loop(t_game_entity *entity)
{
	int			i;

	(void)entity;
	i = -1;
	while (++i < MEM_SIZE)
	{
		ft_printf("%02x ", entity->bg[i]);
		if (i % 64 == 63)
			ft_printf("\n");
	}
	
}
