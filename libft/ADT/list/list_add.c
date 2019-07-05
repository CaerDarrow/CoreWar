/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 18:29:59 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/05 16:56:56 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"



void						int_array_as_list(t_list **l, int i, ...)
{
	int						num;
	va_list					ap;

	num = 0;
	va_start(ap, i);
	while (i-- > 0)
	{
		ld_push_back(l, ft_int_get_mass((num = va_arg(ap, int))));
	}
	va_end(ap);
}

int							ld_push_back(t_list **l, void *data)
{
	t_list					*t;

	if (!l || !data)
		return (0);
	if (!*l)
		return ((*l = l_create(data, NULL)) != NULL);
	t = *l;
	while (t->next)
		t = t->next;
	if (!(t->next = l_create(data, t)))
		return (0);
	return (1);
}

int							ld_push_front(t_list **l, void *data)
{
	t_list					*t;

	if (!l || !data)
		return (0);
	if (!*l)
		return ((*l = l_create(data, NULL)) != NULL);
	t = *l;
	t->prev = l_create(data, NULL);
	*l = t->prev;
	(*l)->next = t;
	return (1);
}

int							l_push_back(t_list **l, t_list *e)
{
	t_list					*t;

	if (!l || !e)
		return (0);
	if (!*l)
	{
		e->prev = NULL;
		*l = e;
		return (1);
	}
	t = *l;
	while (t->next)
		t = t->next;
	e->prev = t;
	t->next = e;
	return (1);
}

int							l_push_front(t_list **l, t_list *e)
{
	if (!l || !e)
		return (0);
	if (!*l)
	{
		e->prev = NULL;
		*l = e;
		return (1);
	}
	e->next = *l;
	*l = e;
	e->prev = NULL;
	return (1);
}
