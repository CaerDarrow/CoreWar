/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 11:03:39 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 17:45:02 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	key_press(int keycode, void *param)
{
	t_game_entity	*entity;
	static int		move_key = 1;

	entity = (t_game_entity *)param;
	if (keycode == RETURN)
	{
		move_key == 1 ? VIS->loop_key = !VIS->loop_key : 0;
		move_key = 1;
	}
	else if (keycode == B_SPACE || keycode == ARROW_RIGHT ||
				keycode == ARROW_LEFT)
		VIS->loop_key = 0;
	if (keycode == B_SPACE || keycode == ARROW_RIGHT)
	{
		if (move_key == 1 && (BACKLOG == NULL || BACKLOG->prev == NULL))
			game_loop(entity) == 1 ? VIS->loop_key = 2 : 0;
		else if (move_key == 1)
			move_log_front(entity);
		move_key = 1;
	}
	else if (keycode == ARROW_LEFT)
		move_log_back(entity);
	else if (keycode == EXIT)
		exit(0);
	return (0);
}
