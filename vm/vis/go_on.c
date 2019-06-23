/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_on.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 17:43:16 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 17:43:22 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	go_on(t_game_entity *entity)
{
	t_visualizer *vis;

	vis = entity->vis;
	vis->cycle = entity->cycle;
	if (SIDE_SQUARE > 4)
		draw_log_scale(vis, 1);
	mlx_put_image_to_window(WIN->mlx, WIN->win, WIN->image, 0, 0);
	draw_menu(vis);
	add_log(vis);
}
