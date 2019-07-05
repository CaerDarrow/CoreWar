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

static void	move_front_auto(t_visualizer *vis, int keycode, int *move_key)
{
	if (keycode == RETURN)
	{
		if (*move_key == 1)
			vis->loop_key = !vis->loop_key;
		*move_key = 1;
	}
	else if (keycode == B_SPACE || keycode == ARROW_RIGHT ||
			keycode == ARROW_LEFT)
		vis->loop_key = 0;
}

static void	move_front(t_game_entity *entity, int keycode, int *move_key)
{
	t_visualizer *vis;

	vis = entity->vis;
	if (keycode == B_SPACE || keycode == ARROW_RIGHT)
	{
		if (*move_key == 1 && (BACKLOG == NULL || BACKLOG->prev == NULL))
		{
			if (prep_game_loop(entity) == 1)
				vis->loop_key = 2;
		}
		else if (*move_key == 1)
			move_log_front(vis);
		*move_key = 1;
	}
}

static void	move_back(t_visualizer *vis, int keycode)
{
	if (keycode == ARROW_LEFT)
		move_log_back(vis);
}

int			key_press(int keycode, void *param)
{
	t_game_entity	*entity;
	t_visualizer	*vis;
	static int		move_key = 1;

	entity = (t_game_entity *)param;
	vis = entity->vis;
	move_front_auto(vis, keycode, &move_key);
	move_front(entity, keycode, &move_key);
	move_back(vis, keycode);
	if (keycode == EXIT)
		exit(0);
	return (0);
}
