/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_log.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 18:07:22 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 18:07:24 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_log	*inicialization_log(t_game_entity *entity)
{
	t_log		*new_log;
	const int	size_data = sizeof(int) * (SIZE_FIELD_X) * SIZE_FIELD_Y;

	if (!(new_log = (t_log *)malloc(sizeof(t_log))))
		error("Malloc error");
	if (!(new_log->data = (int *)malloc(sizeof(int) * size_data)))
		error("Malloc error");
	ft_memcpy(new_log->data, WIN->data, size_data);
	ft_memcpy(new_log->percents, VIS->percents, sizeof(int) * 4);
	new_log->cycle = entity->cycle;
	return (new_log);
}

static void		del_last_log(t_list **last_list)
{
	t_list	*prev;
	t_log	*log;

	prev = (*last_list)->prev;
	prev->next = NULL;
	log = (t_log *)(*last_list)->data;
	ft_memdel((void **)&(log->data));
	ft_memdel((void **)&log);
	ft_memdel((void **)last_list);
	*last_list = prev;
}

void			add_log(t_game_entity *entity)
{
	static t_list	*last_list;
	t_log			*new_log;

	if (VIS->num_logs > NUM_LOGS)
		del_last_log(&last_list);
	else
		VIS->num_logs++;
	new_log = inicialization_log(entity);
	ld_push_front(&(VIS->backlog), new_log);
	if (VIS->num_logs == 1)
		last_list = VIS->backlog;
}

void			move_log_back(t_game_entity *entity)
{
	if (BACKLOG == NULL || BACKLOG->next == NULL)
		return ;
	ft_memcpy(WIN->data, ((t_log *)BACKLOG->data)->data, sizeof(int) *
			SIZE_FIELD_X * SIZE_FIELD_Y);
	ft_memcpy(VIS->percents, ((t_log *)BACKLOG->data)->percents,
		sizeof(int) * 4);
	entity->cycle = ((t_log *)BACKLOG->data)->cycle;
	VIS->backlog = BACKLOG->next;
	if (SIDE_SQUARE > 4)
		draw_log_scale(entity, -1);
	mlx_put_image_to_window(WIN->mlx, WIN->win, WIN->image, 0, 0);
	draw_menu(entity);
	VIS->num_logs--;
}

void			move_log_front(t_game_entity *entity)
{
	int log_scale_position;

	BACKLOG = BACKLOG->prev;
	ft_memcpy(WIN->data, ((t_log *)BACKLOG->data)->data,
			sizeof(int) * SIZE_FIELD_X * SIZE_FIELD_Y);
	ft_memcpy(VIS->percents, ((t_log *)BACKLOG->data)->percents,
		sizeof(int) * 4);
	entity->cycle = ((t_log *)BACKLOG->data)->cycle;
	if (SIDE_SQUARE > 4)
	{
		draw_log_scale(entity, 1);
		log_scale_position = TML->log_scale_position++;
		draw_end_pixels_forvard(entity, RGB_GRAY);
		TML->log_scale_position = log_scale_position;
	}
	mlx_put_image_to_window(WIN->mlx, WIN->win, WIN->image, 0, 0);
	draw_menu(entity);
	VIS->num_logs++;
}
