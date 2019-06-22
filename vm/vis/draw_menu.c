/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 17:21:55 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 17:21:58 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	draw_menu(t_game_entity *entity)
{
	const int x = LOG_SCALE_X;
	const int y = LINE_WIDTH * 8 - 13;

	if (SIDE_SQUARE > 4)
	{
		mlx_string_put(WIN->mlx, WIN->win, x, y, RGB_WHITE, "LOG SCALE");
		draw_percent(entity);
		draw_legend(entity);
		draw_instructions(entity);
		draw_cycle(entity);
	}
}
