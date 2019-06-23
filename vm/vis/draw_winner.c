/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_winner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 17:35:37 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 17:35:42 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		squares_winner(t_visualizer *vis, int prev_color, int color)
{
	int	num_pixel;
	int x_y[2];
	int i;

	x_y_square(vis, SQ->num_sq);
	num_pixel = get_num_pixel(vis, SQ->x, SQ->y);
	if (WIN->data[num_pixel] != prev_color)
		return ;
	i = -1;
	x_y[0] = SQ->x;
	x_y[1] = SQ->y;
	while (++i < SIDE_SQUARE)
	{
		draw_horizontal_line(vis, x_y, SIDE_SQUARE, color);
		x_y[1] += 1;
	}
}

static void		draw_winners_squares(t_visualizer *vis, int winner)
{
	static int	color;
	static int	prev_color;

	if (color == 0)
	{
		prev_color = PLAYERS.players_colors[winner - 1];
		color = RGB_RED + 1;
	}
	else if (color >= 16777216)
		color = RGB_RED + 1;
	else
	{
		color += 5;
		if (color == PLAYERS.players_colors[0] ||
				color == PLAYERS.players_colors[1] ||
				color == PLAYERS.players_colors[2] ||
				color == PLAYERS.players_colors[3] || color == RGB_BLACK)
			color += 5;
	}
	SQ->num_sq = -1;
	while (++SQ->num_sq < MEM_SIZE)
		squares_winner(vis, prev_color, color);
	prev_color = color;
}

int				draw_winner(t_visualizer *vis, int winer)
{
	const char	races[4][10] = {"Horde", "Alliance", "Undead", "Sentinels"};
	const char	players[4][10] = {"Player 1", "Player 2", "Player 3",
									"Player 4"};
	const int	interval = LINE_WIDTH * (2 + winer);
	static int	color;
	char		*str;

	if (SIDE_SQUARE != WARCRAFT_SQUARE)
		draw_winners_squares(vis, winer);
	mlx_put_image_to_window(WIN->mlx, WIN->win, WIN->image, 0, 0);
	if (SIDE_SQUARE > 4)
	{
		draw_menu(vis);
		if (color == 0 || color >= 0xFFFFFF)
			color = RGB_RED;
		else
			color += 5;
		SQ->x = INDENT_LEGEND_X;
		SQ->y = interval;
		clear_area(vis, (10 * 8), (25));
		str = (char *)(SIDE_SQUARE == WARCRAFT_SQUARE ? races[winer - 1] :
				players[winer - 1]);
		mlx_string_put(WIN->mlx, WIN->win, SQ->x, SQ->y, color, str);
	}
	return (0);
}
