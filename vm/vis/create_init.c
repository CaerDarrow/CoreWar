/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 13:14:28 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 16:08:19 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_square		*inicialization_square(void)
{
	t_square	*sq;

	if (!(sq = (t_square *)malloc(sizeof(t_square))))
		error("Malloc error");
	sq->x = INDENT_SQUARE_X;
	sq->y = INDENT_SQUARE_Y;
	sq->num_sq = 0;
	return (sq);
}

static int			size_window_x(t_visualizer *vis)
{
	if (SIDE_SQUARE > 4)
		return (INDENT_SQUARE_X * 2 + (FIELD_SIDE * SIDE_SQ_WID - GRID_WIDTH +
				SIZE_MENU));
	else
		return (INDENT_SQUARE_X * 2 + (FIELD_SIDE * SIDE_SQ_WID - GRID_WIDTH));
}

static t_window		*inicialization_window(t_visualizer *vis)
{
	t_window	*win;
	int			size_line;
	int			bits_per_pixel;
	int			endian;

	if (!(win = (t_window *)malloc(sizeof(t_window))))
		error("Malloc error");
	WIN = win;
	win->mlx = mlx_init();
	SIZE_FIELD_X = size_window_x(vis);
	win->win = mlx_new_window(win->mlx, SIZE_FIELD_X, SIZE_FIELD_Y,
			SIDE_SQUARE == WARCRAFT_SQUARE ? "coreWARCRAFT" :
			"ZDES' MOGLA Bbl BblTb VASHA REKLAMA");
	bits_per_pixel = 8;
	win->image = mlx_new_image(win->mlx, SIZE_FIELD_X, SIZE_FIELD_Y);
	win->data = (int *)mlx_get_data_addr(win->image, &bits_per_pixel,
			&size_line, &endian);
	mlx_put_image_to_window(win->mlx, win->win, win->image, 0, 0);
	return (win);
}

static t_log_scale	*inicialization_log_scale(t_visualizer *vis)
{
	t_log_scale *log_scale;

	if (!(log_scale = (t_log_scale *)malloc(sizeof(t_log_scale))))
		error("Malloc error");
	log_scale->log_scale_position = SIZE_FIELD_X - SIZE_MENU + LETER_X * 2;
	return (log_scale);
}

t_visualizer		*inicialization_vis(t_game_entity *entity)
{
	t_visualizer	*vis;

	if (!(vis = (t_visualizer *)malloc(sizeof(t_visualizer))))
		error("Malloc error");
	entity->vis = vis;
	SIDE_SQUARE = KEK;
	vis->n_players = entity->n_players;
	vis->num_logs = 0;
	vis->loop_key = 0;
	vis->win = inicialization_window(vis);
	vis->log_scale = inicialization_log_scale(vis);
	vis->sq = inicialization_square();
	vis->pictures.player1 = get_player1(vis);
	vis->pictures.player2 = get_player2(vis);
	vis->pictures.player3 = get_player3(vis);
	vis->pictures.player4 = get_player4(vis);
	PLAYERS.players_colors[0] = PLAYER_1;
	PLAYERS.players_colors[1] = PLAYER_2;
	PLAYERS.players_colors[2] = PLAYER_3;
	PLAYERS.players_colors[3] = PLAYER_4;
	ft_memset(PLAYERS.percents, -1, sizeof(char) * 4);
	ft_memset(PLAYERS.occupied_cells, -1, sizeof(char) * 4);
	BACKLOG = NULL;
	return (vis);
}
