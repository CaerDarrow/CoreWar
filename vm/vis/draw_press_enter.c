/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_press_enter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 17:25:05 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 17:25:08 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	draw_press_enter(t_visualizer *vis)
{
	const int	x = LOG_SCALE_X;
	const int	y = LINE_WIDTH * 8 - 13;
	static int	color;

	if (color == 0 || color >= 0xFFFFFF)
		color = RGB_RED;
	else
		color += 5;
	mlx_put_image_to_window(WIN->mlx, WIN->win, WIN->image, 0, 0);
	if (SIDE_SQUARE > 4)
	{
		mlx_string_put(WIN->mlx, WIN->win, x, y, RGB_WHITE, "LOG SCALE");
		draw_percent(vis);
		draw_legend(vis);
		draw_cycle(vis);
		SQ->x = INDENT_LEGEND_X + LETER_X * 5;
		SQ->y = LINE_WIDTH * 12 + LETER_Y;
		clear_area(vis, LETER_X * 12, LETER_Y);
		mlx_string_put(WIN->mlx, WIN->win, SQ->x, SQ->y, color, "PRESS "
																"ENTER");
	}
}
