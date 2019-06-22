/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_legend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 17:01:52 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 17:01:56 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char	*get_str_player(int i)
{
	char		*str;
	char		*buf;

	str = ft_itoa(i);
	buf = ft_strjoin("Player ", str);
	free(str);
	return (buf);
}

void		draw_legend(t_game_entity *entity)
{
	const char	races[4][10] = {"Horde", "Alliance", "Undead", "Sentinels"};
	int			interval;
	char		*buf;
	int			i;

	mlx_string_put(WIN->mlx, WIN->win, CYCLE_X, LINE_WIDTH, RGB_WHITE, "CYCLE");
	i = 0;
	interval = LINE_WIDTH * 3;
	while (++i <= entity->n_players)
	{
		if (SIDE_SQUARE != 18)
			buf = get_str_player(i);
		else
			buf = (char *)races[i - 1];
		mlx_string_put(WIN->mlx, WIN->win, INDENT_LEGEND_X, interval,
			RGB_WHITE, buf);
		mlx_string_put(WIN->mlx, WIN->win, INDENT_LEGEND_X + LETER_X * 10,
			interval, RGB_WHITE, ":");
		SIDE_SQUARE != 18 ? free(buf) : 0;
		interval += LINE_WIDTH;
	}
}
