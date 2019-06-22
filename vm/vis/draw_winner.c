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

static void		squares_winner(t_game_entity *entity, int prev_color, int color)
{
	int	num_pixel;
	int x_y[2];
	int i;

	x_y_square(entity, SQ->num_sq);
	num_pixel = get_num_pixel(entity, SQ->x, SQ->y);
	if (WIN->data[num_pixel] != prev_color)
		return ;
	i = -1;
	x_y[0] = SQ->x;
	x_y[1] = SQ->y;
	while (++i < SIDE_SQUARE)
	{
		draw_horizontal_line(entity, x_y, SIDE_SQUARE, color);
		x_y[1] += 1;
	}
}

static void		draw_winners_squares(t_game_entity *entity, int winner)
{
	static int	color;
	static int	prev_color;

	if (color == 0 || color >= 0xFFFFFF)
	{
		prev_color = VIS->players_colors[winner - 1];
		color = RGB_RED + 1;
	}
	else
	{
		color += 5;
		if (color == VIS->players_colors[0] ||
				color == VIS->players_colors[1] ||
				color == VIS->players_colors[2] ||
				color == VIS->players_colors[3])
			color += 5;
	}
	SQ->num_sq = 0;
	while (SQ->num_sq < MEM_SIZE)
	{
		squares_winner(entity, prev_color, color);
		SQ->num_sq++;
	}
	prev_color = color;
}

int				draw_winner(t_game_entity *entity, int winer)
{
	const char	races[4][10] = {"Horde", "Alliance", "Undead", "Sentinels"};
	const char	players[4][10] = {"Player 1", "Player 2", "Player 3",
									"Player 4"};
	const int	interval = LINE_WIDTH * (2 + winer);
	static int	color;
	char		*str;

	if (SIDE_SQUARE != 18)
		draw_winners_squares(entity, 4);
	mlx_put_image_to_window(WIN->mlx, WIN->win, WIN->image, 0, 0);
	if (SIDE_SQUARE > 4)
	{
		draw_menu(entity);
		if (color == 0 || color >= 0xFFFFFF)
			color = RGB_RED;
		else
			color += 5;
		SQ->x = INDENT_LEGEND_X;
		SQ->y = interval;
		clear_area(entity, (10 * 8), (25));
		str = (char *)(SIDE_SQUARE == 18 ? races[winer - 1] :
				players[winer - 1]);
		mlx_string_put(WIN->mlx, WIN->win, SQ->x, SQ->y, color, str);
	}
	return (0);
}
