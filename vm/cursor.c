/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:19:26 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/29 21:17:43 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_cursor		*cursor_create(int id)
{
	t_cursor	*c;
	int			i;

	if (!(c = (t_cursor *)malloc(sizeof(t_cursor))))
		error("Malloc error");
	ft_bzero(c, sizeof(t_cursor));
	if (!(c->reg = (char **)malloc(17 * sizeof(char *))))
		error("Malloc error");
	i = -1;
	while (++i < 16)
	{
		if (!(c->reg[i] = (char *)malloc(REG_SIZE)))
			error("Malloc error");
		ft_bzero(c->reg[i], REG_SIZE);
		set_reg_num(c, 1, id);
	}
	c->reg[i] = 0;
	return (c);
}

void					destroy_cur(t_list **t)
{
	if (!t || !*t || !(*t)->data)
		error("Cant destroy this cursor(unexpected)");
	ft_freemas(&((t_cursor*)(*t)->data)->reg, 0);
	ft_memdel((void**)&(*t)->data);
	ft_memdel((void**)t);
}

int				cursor_should_die(t_list *c, int cycles_to_die)
{
	if (c && c->data)
		return (((t_cursor *)c->data)->last_live_call - cycles_to_die > 0);
	return (0);
}

void			move_cursor(t_game_entity *entity, t_cursor *cursor)
{
	(void)entity;(void)cursor;

}

void			shift_cycle(t_cursor *cursor)
{
	cursor->cycles_to_exec--;
	if (cursor->cycles_to_exec < 0)///
		error("Something bad happened (unexpected)");///
}
