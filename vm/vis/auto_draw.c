/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_draw_square.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 15:55:11 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 15:57:27 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	prepare_end_game(t_visualizer *vis, int *end_game, int *picture)
{
	*end_game = rand_put_pixel(vis, picture);
	draw_menu(vis);
	vis->loop_key = 1;
	return (0);
}

static void	vis_game_loop(t_game_entity *entity, int *end_game, int **picture,
				int *winner)
{
	t_visualizer *vis;

	vis = entity->vis;
	if (game_loop(entity) == 1)
	{
		if (*winner == 0)
			*winner = choose_winner(entity);
		if (SIDE_SQUARE > 4)
		{
			*picture = get_final_picture(*winner);
			vis->loop_key = 0;
		}
		else
			*end_game = 1;
	}
}

int			auto_draw(void *param)
{
	t_game_entity	*entity;
	t_visualizer	*vis;
	static int		end_game;
	static int		*picture;
	static int		winner;

	entity = (t_game_entity *)param;
	vis = entity->vis;
	if (vis->loop_key && end_game == 1)
		return (draw_winner(vis, winner));
	if (SIDE_SQUARE == WARCRAFT_SQUARE && vis->loop_key && picture != NULL)
		return (prepare_end_game(vis, &end_game, picture));
	else if ((!vis->loop_key || vis->loop_key == 2) && picture != NULL)
		SIDE_SQUARE == WARCRAFT_SQUARE ? draw_press_enter(vis) :
			draw_winner(vis, winner);
	if (vis->loop_key && (BACKLOG == NULL ||
		BACKLOG->prev == NULL) && picture == NULL)
		vis_game_loop(entity, &end_game, &picture, &winner);
	else if (vis->loop_key && BACKLOG != NULL && BACKLOG->prev != NULL)
		move_log_front(vis);
	return (0);
}
