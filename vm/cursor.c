/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:19:26 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/12 16:51:14 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
int				get_num(t_uchar *s, int size)
{
	int			i;
	int			res;

	res = 0;
	i = -1;

	while (++i < size)
		res = (res << 8) | s[i];
	return (res);
}

t_cursor		*cursor_create(t_game_entity *entity, int id)
{
	t_cursor	*c;
	int			i;

	if (!(c = (t_cursor *)malloc(sizeof(t_cursor))))
		error("Malloc error");
	ft_bzero(c, sizeof(t_cursor));
	if (!(c->reg = (t_uchar **)malloc(17 * sizeof(t_uchar *))))
		error("Malloc error");
	i = -1;
	while (++i < 16)
	{
		if (!(c->reg[i] = (t_uchar *)malloc(REG_SIZE * sizeof(t_uchar))))
			error("Malloc error");
		ft_bzero(c->reg[i], REG_SIZE);
		set_reg_num(c, 1, -id);
	}
	c->reg[i] = 0;
	c->id = id;
	c->index = ++entity->alive_cursors;
	c->position = MEM_SIZE * (id - 1) / entity->n_players;
	return (c);
}

void					destroy_cur(t_list **t)
{
	ft_freemas((char ***)&((t_cursor*)(*t)->data)->reg, 0);
	ft_memdel((void**)&(*t)->data);
	ft_memdel((void**)t);
}

int					cursor_should_die(t_list *c, t_game_entity *entity)
{
	if (c && c->data)
		return (entity->cycle - ((t_cursor *)c->data)->last_live_call >= entity->cycles_to_die);
	error("Unexpected error: cursor_should_die()");
	return (0);
}

void			move_cursor(t_game_entity *entity, t_cursor *cursor, int bytes)
{
	wipe_off_cursor(entity, cursor->position);
	if (VERBOSE_LVL(16))
		ft_printf("Cursor %d: Player's %d cursor moved from %d", cursor->index, cursor->id, cursor->position);
	cursor->position = correct_position(cursor->position + bytes);
	draw_cursor(entity, cursor->position, cursor->id - 1);
	if (VERBOSE_LVL(16))
		ft_printf(" to %d\n", cursor->position);
}

void				copy_reg(t_uchar **dest, t_uchar **src)
{
	int				i;

	i = -1;
	while (++i < REG_NUM)
		ft_memcpy(dest[i], src[i], REG_SIZE);
}
