/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 18:15:39 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 18:15:42 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	draw_horizontal_line(t_visualizer *vis, int x_y[2], int length,
			int color)
{
	const int	num_pxl = get_num_pixel(vis, x_y[0], x_y[1]);

	ft_intset(WIN->data + num_pxl, color, length);
}

void	draw_vertical_line(t_visualizer *vis, int x_y[2], int length,
			int color)
{
	int	num_pxl;
	int	i;

	i = -1;
	num_pxl = get_num_pixel(vis, x_y[0], x_y[1]);
	while (++i < length)
	{
		WIN->data[num_pxl] = color;
		num_pxl += SIZE_FIELD_X;
	}
}
