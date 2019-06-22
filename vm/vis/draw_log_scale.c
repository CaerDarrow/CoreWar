/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_log_scale.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 17:17:08 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 17:17:46 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	draw_end_pixels_forvard(t_game_entity *entity, int color)
{
	int	x_y[2];

	x_y[0] = TML->log_scale_position;
	x_y[1] = LINE_WIDTH * 9 - 9;
	while (TML->log_scale_position < SIZE_FIELD_X + LETER_X * 2 -
			INDENT_SQUARE_X - LETER_X * 4)
	{
		draw_vertical_line(entity, x_y, LETER_Y, color);
		TML->log_scale_position++;
		x_y[0]++;
	}
	TML->log_scale_position--;
}

void	draw_back_log_scale(t_game_entity *entity)
{
	int log_scale_position;
	int	x_y[2];

	x_y[0] = TML->log_scale_position;
	x_y[1] = LINE_WIDTH * 9 - 9;
	draw_vertical_line(entity, x_y, LETER_Y, RGB_GRAY);
	TML->log_scale_position--;
	log_scale_position = TML->log_scale_position;
	draw_end_pixels_forvard(entity, RGB_GRAY);
	TML->log_scale_position = log_scale_position;
}

void	draw_log_scale_forvard(t_game_entity *entity)
{
	int	x_y[2];

	x_y[0] = TML->log_scale_position;
	x_y[1] = LINE_WIDTH * 9 - 9;
	draw_vertical_line(entity, x_y, LETER_Y, RGB_RED);
	TML->log_scale_position++;
}

void	draw_log_scale(t_game_entity *entity, int move)
{
	if (VIS->num_logs < 0 || VIS->num_logs > NUM_LOGS)
		return ;
	if (move == -1)
	{
		if (VIS->num_logs >= 1)
			draw_back_log_scale(entity);
	}
	else if (VIS->num_logs < NUM_LOGS)
		draw_log_scale_forvard(entity);
}
