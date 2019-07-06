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

#include "visualizer.h"

static void	change_percents(t_visualizer *vis, int cur_player)
{
	int			num_prev_player;

	num_prev_player = get_num_player(vis, SQ->x, SQ->y);
	if (num_prev_player == cur_player)
		return ;
	if (cur_player == 4)
	{
		PLAYERS.occupied_cells[num_prev_player] -= 1;
		return ;
	}
	if (num_prev_player != 4)
		PLAYERS.occupied_cells[num_prev_player] -= 1;
	PLAYERS.occupied_cells[cur_player] += 1;
}

void		draw_square(t_visualizer *vis, int num_player)
{
	const int	*picture = get_mini_picture(vis, num_player);
	int			num_pixel;
	int			i;

	x_y_square(vis, SQ->num_sq);
	change_percents(vis, num_player);
	num_pixel = get_num_pixel(vis, SQ->x, SQ->y);
	i = -1;
	while (++i < SIDE_SQUARE)
	{
//		ft_printf("%p %p\n", WIN, WIN->data);
//		ft_printf("size %d\n", WIN->data + num_pixel);
		ft_memcpy(WIN->data + num_pixel, picture + SIDE_SQUARE * i,
			sizeof(int) * SIDE_SQUARE);
//		ft_printf("num_player %d\n", num_player);
		num_pixel += SIZE_FIELD_X;
	}
//	ft_printf("i =  %d\n", i);
}
