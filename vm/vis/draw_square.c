/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 17:27:12 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 17:27:13 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	change_percents(t_game_entity *entity, int cur_player)
{
	int			num_prev_player;

	num_prev_player = get_num_player(entity, SQ->x, SQ->y);
	if (num_prev_player == cur_player)
		return ;
	if (cur_player == 4)
	{
		VIS->occupied_cells[num_prev_player] -= 1;
		return ;
	}
	if (num_prev_player != 4)
		VIS->occupied_cells[num_prev_player] -= 1;
	VIS->occupied_cells[cur_player] += 1;
}

void		draw_square(t_game_entity *entity, int num_player)
{
	const int	*picture = get_picture(entity, num_player);
	int			num_pixel;
	int			i;

	x_y_square(entity, SQ->num_sq);
	change_percents(entity, num_player);
	num_pixel = get_num_pixel(entity, SQ->x, SQ->y);
	i = -1;
	while (++i < SIDE_SQUARE)
	{
		ft_memcpy(WIN->data + num_pixel, picture + SIDE_SQUARE * i,
			sizeof(int) * SIDE_SQUARE);
		num_pixel += SIZE_FIELD_X;
	}
}
