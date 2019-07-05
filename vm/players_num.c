/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 19:15:13 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/05 19:36:16 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			memdel_2(void **a, void **b)
{
	ft_memdel(a);
	ft_memdel(b);
}

int					remove_n(t_list **l, int num)
{
	t_list			*t;

	t = *l;
	while (t)
		if (*(int *)t->data == num)
		{
			if (!t->prev)
			{
				t = (*l)->next;
				t ? t->prev = 0 : 0;
				memdel_2((void**)&(*l)->data, (void**)l);
				*l = t;
			}
			else
			{
				t->prev->next = t->next;
				t->next ? t->next->prev = t->prev : 0;
				memdel_2((void**)&t->data, (void**)&t);
			}
			return (1);
		}
		else
			t = t->next;
	return (0);
}

int					get_next_free_number(void)
{
	int				b;

	if (!g_free_player_num)
		error("Invalid -n flag");
	if (g_n_flag <= 0)
	{
		b = *(int *)g_free_player_num->data;
		if (!remove_n(&g_free_player_num, b))
			error("Invalid -n flag");
		return (b);
	}
	b = g_n_flag;
	g_n_flag = -1;
	if (!remove_n(&g_free_player_num, b))
		error("Invalid -n flag");
	return (b);
}
