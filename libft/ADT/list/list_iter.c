/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_iter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:33:55 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/13 18:29:40 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	l_iter(t_list **l, void (*f)(t_list **elem))
{
	t_list	*t;

	if (l && *l)
	{
		t = *l;
		while (t)
		{
			f(&t);
			t = t->next;
		}
	}
}

void	l_delone(t_list **cur, void (*f)(t_list **elem))
{
	t_list *head;

	if (!*cur || !cur)
		return ;
	head = *cur;
	if (head->prev && head->next)
		head->prev->next = head->next;
	else if (!head->prev && head->next)
		head = head->next;
	f(cur);
	ft_memdel((void **)cur);
	cur = &head;
}

void	l_reciter(t_list **l, void (*f1)(t_list **l, void (*f)(t_list **l)),
					void (*f2)(t_list **l))
{
	if (!*l || !l)
		return ;
	l_reciter(&(*l)->next, f1, f2);
	f1(l, f2);
}

void	l_delall(t_list **l, void (*f)(t_list **elem))
{
	if (!*l || !l)
		return ;
	l_reciter(l, l_delone, f);
}
