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

static t_log	*inicialization_log(t_visualizer *vis)
{
	const int	size_data = sizeof(int) * (SIZE_FIELD_X) * SIZE_FIELD_Y;
	t_log		*new_log;

	if (!(new_log = (t_log *)malloc(sizeof(t_log))))
		error("Malloc error");
	if (!(new_log->data = (int *)malloc(sizeof(int) * size_data)))
		error("Malloc error");
	ft_memcpy(new_log->data, WIN->data, size_data);
	ft_memcpy(new_log->percents, PLAYERS.percents, sizeof(int) * 4);
	new_log->cycle = vis->cycle;
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

void			add_log(t_visualizer *vis)
{
	static t_list	*last_list;
	t_log			*new_log;

	if (vis->num_logs > NUM_LOGS)
		del_last_log(&last_list);
	else
		vis->num_logs++;
	new_log = inicialization_log(vis);
	ld_push_front(&(vis->backlog), new_log);
	if (vis->num_logs == 1)
		last_list = vis->backlog;
}

void			move_log_back(t_visualizer *vis)
{
	if (BACKLOG == NULL || BACKLOG->next == NULL)
		return ;
	ft_memcpy(WIN->data, ((t_log *)BACKLOG->data)->data, sizeof(int) *
			SIZE_FIELD_X * SIZE_FIELD_Y);
	ft_memcpy(PLAYERS.percents, ((t_log *)BACKLOG->data)->percents,
		sizeof(int) * 4);
	vis->cycle = ((t_log *)BACKLOG->data)->cycle;
	vis->backlog = BACKLOG->next;
	if (SIDE_SQUARE > 4)
		draw_log_scale(vis, -1);
	mlx_put_image_to_window(WIN->mlx, WIN->win, WIN->image, 0, 0);
	draw_menu(vis);
	vis->num_logs--;
}

void			move_log_front(t_visualizer *vis)
{
	int log_scale_position;

	BACKLOG = BACKLOG->prev;
	ft_memcpy(WIN->data, ((t_log *)BACKLOG->data)->data,
			sizeof(int) * SIZE_FIELD_X * SIZE_FIELD_Y);
	ft_memcpy(PLAYERS.percents, ((t_log *)BACKLOG->data)->percents,
		sizeof(int) * 4);
	vis->cycle = ((t_log *)BACKLOG->data)->cycle;
	if (SIDE_SQUARE > 4)
	{
		draw_log_scale(vis, 1);
		log_scale_position = TML->log_scale_position++;
		draw_log_scale_uptoend(vis, RGB_GRAY);
		TML->log_scale_position = log_scale_position;
	}
	mlx_put_image_to_window(WIN->mlx, WIN->win, WIN->image, 0, 0);
	draw_menu(vis);
	vis->num_logs++;
}
