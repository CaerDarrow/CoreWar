/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:19:26 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/05 15:59:03 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// unsigned char	*num_to_bytes(int n)
// {
// 	unsigned char	*res;
// 	int				size;
// 	int				i;
//
// 	size = 4;
// 	if (!(res = ft_strnew(size)))
// 		error("Malloc error");
// 	i = -1;
// 	while (++i < size)
// 		res[i] = (n >> (6 - i * 2)) & 0xFF;
// 	return (res);
// }

int				get_num(unsigned char *s, int size)
{
	int			i;
	int			res;

	res = 0;
	i = -1;

	while (++i < size)
		res = (res << 8) | s[i];
	// res = (cursor->reg[0][0] << 24) | (cursor->reg[0][1] << 16) | (cursor->reg[0][2] << 8) | cursor->reg[0][3];
	return (res);
}

t_cursor		*cursor_create(int id, char players)
{
	t_cursor	*c;
	int			i;

	if (!(c = (t_cursor *)malloc(sizeof(t_cursor))))
		error("Malloc error");
	ft_bzero(c, sizeof(t_cursor));
	if (!(c->reg = (unsigned char **)malloc(17 * sizeof(unsigned char *))))
		error("Malloc error");
	i = -1;
	while (++i < 16)
	{
		if (!(c->reg[i] = (unsigned char *)malloc(REG_SIZE * sizeof(unsigned char))))
			error("Malloc error");
		ft_bzero(c->reg[i], REG_SIZE);
		set_reg_num(c, 1, -id);
		// ft_printf("%d\n", get_player_num(c));
	}
	c->reg[i] = 0;
	c->moved = 1;
	c->id = id;
	c->position = MEM_SIZE * (id - 1) / players;
	return (c);
}

void					destroy_cur(t_list **t)
{
	if (!t || !*t || !(*t)->data)
		error("Cant destroy this cursor(unexpected)");
	ft_freemas((char ***)&((t_cursor*)(*t)->data)->reg, 0);
	ft_memdel((void**)&(*t)->data);
	ft_memdel((void**)t);
}

int				cursor_should_die(t_list *c, int cycles_to_die)
{
	if (c && c->data)
		return (((t_cursor *)c->data)->last_live_call - cycles_to_die < 0);
	ft_printf("Unexpected\n");
	return (0);
}

void			move_cursor(t_cursor *cursor, int bytes)
{
	cursor->position = (cursor->position + bytes) % MEM_SIZE;
}
