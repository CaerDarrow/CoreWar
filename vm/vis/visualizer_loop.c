/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 11:04:03 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/02 11:04:04 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	close_mlx(void *param)
{
	(void)param;
	exit(0);
}

void		visualizer_loop(t_game_entity *entity)
{
	mlx_hook(WIN->win, 2, 0, key_press, entity);
	mlx_hook(WIN->win, 17, 0, close_mlx, NULL);
	mlx_loop_hook(WIN->mlx, auto_draw_square, entity);
	mlx_loop(WIN->mlx);
}
