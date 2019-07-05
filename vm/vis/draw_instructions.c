/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_instrictions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 16:55:22 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 16:57:36 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	isolate_or(t_visualizer *vis, const char inst[11][14], int *j,
			int interval)
{
	mlx_string_put(WIN->mlx, WIN->win,
		INDENT_LEGEND_X +
		(ft_strlen(inst[*j - 2]) + ft_strlen(inst[*j - 1])) * LETER_X,
		interval,
		RGB_WHITE,
		(char *)inst[*j]);
	mlx_string_put(WIN->mlx, WIN->win,
		INDENT_LEGEND_X + (ft_strlen(inst[*j - 2]) + ft_strlen(inst[*j - 1]) +
		ft_strlen(inst[*j])) * LETER_X,
		interval,
		RGB_LIGHT_GREEN,
		(char *)inst[*j + 1]);
	*j += 2;
}

void		draw_instructions(t_visualizer *vis)
{
	const char	inst[11][14] = {
								"auto pilot : ", "ENTER",
								"move       : ", "SPACE", " or ", "->",
								"move back  : ", "<-",
								"exit       : ", "ESC"};
	int			interval;
	int			i;
	int			j;

	i = 0;
	j = 0;
	interval = LINE_WIDTH * 11;
	while (++i < 5)
	{
		mlx_string_put(WIN->mlx, WIN->win, INDENT_LEGEND_X,
			interval, RGB_WHITE, (char *)inst[j]);
		mlx_string_put(WIN->mlx, WIN->win,
			INDENT_LEGEND_X + ft_strlen(inst[j]) * LETER_X,
			interval, RGB_LIGHT_GREEN, (char *)inst[j + 1]);
		j += 2;
		if (j == 4)
			isolate_or(vis, inst, &j, interval);
		interval += LINE_WIDTH;
	}
}
