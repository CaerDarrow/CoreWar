/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 18:23:26 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 18:23:30 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	put_horisontal(t_visualizer *vis, int x_y[2], int i)
{
	const int len = SIZE_MENU - INDENT_SQUARE_X;

	x_y[1] = INDENT_SQUARE_Y + i;
	draw_horizontal_line(vis, x_y, len, RGB_WHITE);
	x_y[1] = LINE_WIDTH * 10 + i;
	draw_horizontal_line(vis, x_y, len, RGB_WHITE);
	x_y[1] = SIZE_FIELD_Y - INDENT_SQUARE_Y - 1 - i;
	draw_horizontal_line(vis, x_y, len, RGB_WHITE);
}

static void	put_vertical(t_visualizer *vis, int x_y[2], int i)
{
	const int len = SIZE_FIELD_Y - INDENT_SQUARE_Y * 2;

	x_y[0] = SIZE_FIELD_X - SIZE_MENU + i;
	draw_vertical_line(vis, x_y, len, RGB_WHITE);
	x_y[0] = SIZE_FIELD_X - INDENT_SQUARE_X - i;
	draw_vertical_line(vis, x_y, len, RGB_WHITE);
}

void		draw_frame(t_visualizer *vis)
{
	int x_y[2];
	int i;

	i = -1;
	x_y[0] = SIZE_FIELD_X - SIZE_MENU;
	while (++i < FRAME_WIDTH)
	{
		put_horisontal(vis, x_y, i);
	}
	i = -1;
	x_y[1] = INDENT_SQUARE_Y;
	while (++i < FRAME_WIDTH)
	{
		put_vertical(vis, x_y, i);
	}
}
