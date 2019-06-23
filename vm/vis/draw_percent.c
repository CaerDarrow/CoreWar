/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_percent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 17:22:46 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 17:22:49 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	draw_percent(t_visualizer *vis)
{
	int			interval;
	char		*str;
	char		*buf;
	int			i;

	interval = LINE_WIDTH * 3;
	i = 0;
	while (++i <= vis->n_players)
	{
		PLAYERS.percents[i - 1] =
				PLAYERS.occupied_cells[i - 1] * 100 / MEM_SIZE;
		str = ft_itoa(PLAYERS.percents[i - 1]);
		buf = ft_strjoin(str, "%");
		free(str);
		SQ->x = INDENT_LEGEND_X + LETER_X * 10;
		SQ->y = interval;
		clear_area(vis, LETER_X * 6, LETER_Y);
		mlx_string_put(WIN->mlx, WIN->win, INDENT_LEGEND_X + LETER_X * 14,
			interval, PLAYERS.players_colors[i - 1], buf);
		free(buf);
		interval += LINE_WIDTH;
	}
}
