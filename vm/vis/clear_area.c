/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_area.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 15:58:57 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 15:58:59 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	clear_area(t_game_entity *entity, int x, int y)
{
	int i;
	int x_y[2];

	i = y;
	x_y[0] = SQ->x;
	x_y[1] = SQ->y;
	while (i-- > 0)
	{
		draw_horizontal_line(entity, x_y, x, RGB_BLACK);
		x_y[0] += SIZE_FIELD_X;
	}
}
