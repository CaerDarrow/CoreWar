/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_y_squrae.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 18:12:30 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 18:12:32 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void			x_y_square(t_visualizer *vis, int num_sq)
{
	const int x = num_sq % FIELD_SIDE;
	const int y = num_sq / FIELD_SIDE;

	SQ->x = INDENT_SQUARE_X + (x * SIDE_SQ_WID);
	SQ->y = INDENT_SQUARE_Y + (y * SIDE_SQ_WID);
}
