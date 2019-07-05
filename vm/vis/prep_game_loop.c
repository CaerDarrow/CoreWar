/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_game_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 13:39:53 by gleonett          #+#    #+#             */
/*   Updated: 2019/07/05 13:39:57 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	prep_game_loop(t_game_entity *entity)
{
	static char end_cycle_flag;

	if (entity->cursors != NULL)
	{
		game_loop(entity);
		go_on(entity);
		entity->cycle++;
		return (0);
	}
	else if (end_cycle_flag == 0)
	{
		end_cycle_flag = 1;
		go_on(entity);
		return (1);
	}
	return (1);
}
