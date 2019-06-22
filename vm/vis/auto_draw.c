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

static int	prepare_end_game(t_game_entity *entity, int *end_game, int *picture)
{
	*end_game = rand_put_pixel(entity, picture);
	draw_menu(entity);
	VIS->loop_key = 1;
	return (0);
}

static void	vis_game_loop(t_game_entity *entity, int *end_game, int **picture,
				int winner)
{
	if (game_loop(entity) == 1)
	{
		if (SIDE_SQUARE > 4)
		{
			*picture = get_final_picture(winner);
			VIS->loop_key = 0;
		}
		else
			*end_game = 1;
	}
}

int			auto_draw_square(void *param)
{
	t_game_entity	*entity;
	static int		end_game;
	static int		*picture;
	const int		winner = 3;

	entity = (t_game_entity *)param;
	if (VIS->loop_key && end_game == 1)
		return (draw_winner(entity, winner));
	if (SIDE_SQUARE == 18 && VIS->loop_key && picture != NULL)
		return (prepare_end_game(entity, &end_game, picture));
	else if ((!VIS->loop_key || VIS->loop_key == 2) && picture != NULL)
		SIDE_SQUARE == 18 ? draw_press_enter(entity) :
					draw_winner(entity, winner);
	if (VIS->loop_key && (BACKLOG == NULL ||
		BACKLOG->prev == NULL) && picture == NULL)
		vis_game_loop(entity, &end_game, &picture, winner);
	else if (VIS->loop_key && BACKLOG != NULL && BACKLOG->prev != NULL)
		move_log_front(entity);
	return (0);
}
