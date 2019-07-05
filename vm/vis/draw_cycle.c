/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 12:32:52 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/23 12:32:55 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	clear_cycle(t_visualizer *vis)
{
	SQ->x = CYCLE_X - 5 * LETER_X;
	SQ->y = LINE_WIDTH + LEGEND_INDENT_Y;
	clear_area(vis, LETER_X * 15, LETER_Y);
}

void		draw_cycle(t_visualizer *vis)
{
	const int	x = CYCLE_X;
	const int	y = LINE_WIDTH + LEGEND_INDENT_Y;
	char		*cycle_str;
	int			indent;

	clear_cycle(vis);
	cycle_str = ft_itoa(vis->cycle);
	if ((indent = ft_strlen(cycle_str)) == 1)
		indent = 2;
	else if (indent == 2 || indent == 3)
		indent = 1;
	else if (indent == 4 || indent == 5)
		indent = 0;
	else if (indent == 6 || indent == 7)
		indent = -1;
	else
		indent = -2;
	mlx_string_put(WIN->mlx, WIN->win, x + indent * LETER_X, y, RGB_RED,
		cycle_str);
	free(cycle_str);
}
