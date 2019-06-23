/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 16:09:28 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 16:10:04 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	draw_cursor(t_visualizer *vis, int position, int id)
{
	const int	len = SIDE_SQUARE + 1;
	const int	color = PLAYERS.players_colors[id];
	int			x_y[2];

	x_y_square(vis, position);
	x_y[0] = SQ->x - 1;
	x_y[1] = SQ->y - 1;
	draw_vertical_line(vis, x_y, len, color);
	draw_horizontal_line(vis, x_y, len, color);
	x_y[1] += len;
	draw_horizontal_line(vis, x_y, len, color);
	x_y[1] -= len;
	x_y[0] += len;
	draw_vertical_line(vis, x_y, len + 1, color);
}

void	wipe_off_cursor(t_visualizer *vis, int position)
{
	const int	len = SIDE_SQUARE + 1;
	const int	color = RGB_BLACK;
	int			x_y[2];

	x_y_square(vis, position);
	x_y[0] = SQ->x - 1;
	x_y[1] = SQ->y - 1;
	draw_vertical_line(vis, x_y, len, color);
	draw_horizontal_line(vis, x_y, len, color);
	x_y[1] += len;
	draw_horizontal_line(vis, x_y, len, color);
	x_y[1] -= len;
	x_y[0] += len;
	draw_vertical_line(vis, x_y, len + 1, color);
}
