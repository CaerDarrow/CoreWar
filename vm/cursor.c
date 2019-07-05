/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:27:08 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/04 22:17:41 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_cursor		*cursor_create(t_game_entity *entity, int id)
{
	t_cursor	*c;
	int			i;

	if (!(c = (t_cursor *)malloc(sizeof(t_cursor))))
		error("Malloc error");
	ft_bzero(c, sizeof(t_cursor));
	i = -1;
	while (++i < (REG_NUM))
		ft_bzero(c->reg[i], (REG_SIZE));
	set_reg_num(c, 1, -id);
	c->id = id;
	c->index = ++entity->alive_cursors;
	c->position = MEM_SIZE * (id - 1) / entity->n_players;
	return (c);
}

void			destroy_cur(t_list **t)
{
	ft_memdel((void**)&(*t)->data);
	ft_memdel((void**)t);
}

int				cursor_should_die(t_cursor *cursor, t_game_entity *entity)
{
	return (entity->cycle - cursor->last_live_call >= entity->cycles_to_die);
}

void			move_cursor(t_game_entity *entity, t_cursor *cursor, int bytes)
{
	entity->vis_key ? wipe_off_cursor(entity->vis, cursor->position) : 0;
	cursor->position = correct_position(cursor->position + bytes);
	entity->vis_key ? draw_cursor(entity->vis, cursor->position,
			cursor->id - 1) : 0;
}

void			copy_reg(t_uchar dest[REG_NUM][REG_SIZE],
					t_uchar src[REG_NUM][REG_SIZE])
{
	int			i;

	i = -1;
	while (++i < REG_NUM)
		ft_memcpy(dest[i], src[i], REG_SIZE);
}
