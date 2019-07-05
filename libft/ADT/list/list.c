/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 12:15:38 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/05 16:52:51 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t						l_size(t_list *lst)
{
	size_t					res;

	res = 0;
	while (lst)
	{
		res++;
		lst = lst->next;
	}
	return (res);
}

size_t						l_full_size(t_list *l)
{
	size_t					res;

	while (l && l->prev)
		l = l->prev;
	res = 0;
	while (l)
	{
		res++;
		l = l->next;
	}
	return (res);
}

t_list						*l_last(t_list *l)
{
	while (l->next)
		l = l->next;
	return (l);
}

void						l_reverse(t_list **l)
{
	t_list					*t;
	t_list					*next;

	t = *l;
	while (t)
	{
		next = t->next;
		t->next = t->prev;
		if (next)
			t = next;
		else
			break ;
	}
	*l = t;
}

t_list						*l_create(void *data, t_list *prev)
{
	t_list					*lst;

	if (!(lst = (t_list*)malloc(sizeof(t_list))))
		return ((t_list*)ft_ptr_free(&data));
	lst->next = NULL;
	lst->prev = prev;
	lst->data = data;
	return (lst);
}
