/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 13:07:30 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 18:10:27 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		draw_champion(t_game_entity *entity, int prog_size, int player)
{
	int i;

	i = -1;
	draw_cursor(entity, SQ->num_sq, player);
	while (++i < prog_size)
	{
		draw_square(entity, player);
		SQ->num_sq += 1;
	}
}

static void		draw_field(t_game_entity *entity)
{
	int			player;
	t_list		*i;

	player = 0;
	i = entity->players;
	while (i != NULL)
	{
		SQ->num_sq = (MEM_SIZE / entity->n_players) * player;
		draw_champion(entity, ((t_header *)i->data)->prog_size, player);
		VIS->occupied_cells[player] = ((t_header *)i->data)->prog_size;
		i = i->next;
		player++;
	}
}

static void		draw_empty_log_scale(t_game_entity *entity)
{
	int width;
	int x_y[2];

	width = -1;
	x_y[0] = SIZE_FIELD_X - SIZE_MENU + LETER_X * 2;
	x_y[1] = LINE_WIDTH * 9 + LETER_Y - 10;
	while (++width < LETER_Y)
	{
		draw_horizontal_line(entity, x_y,
			SIZE_MENU - INDENT_SQUARE_X - LETER_X * 4, RGB_GRAY);
		x_y[1]--;
	}
}

void			init_field(t_game_entity *entity)
{
	inicialization_vis(entity);
	if (SIDE_SQUARE > 4)
	{
		draw_frame(entity);
		draw_empty_log_scale(entity);
	}
	draw_field(entity);
	mlx_put_image_to_window(WIN->mlx, WIN->win, WIN->image, 0, 0);
	if (SIDE_SQUARE > 4)
	{
		draw_percent(entity);
		draw_menu(entity);
	}
}
