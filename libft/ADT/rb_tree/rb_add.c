/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:46:15 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/13 19:11:32 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_rb_tree		*rb_node_create(void *data, long long index, t_rb_tree *parent)
{
	t_rb_tree	*tr;

	if (!(tr = (t_rb_tree *)malloc(sizeof(t_rb_tree))))
		return (NULL);
	tr->right = NULL;
	tr->left = NULL;
	tr->parent = parent;
	tr->index = index;
	tr->data = data;
	if (!parent)
		tr->clr = B;
	else
		// tr->clr = !parent->clr;
		tr->clr = R;
	return (tr);
}


int				rb_push(t_rb_tree **root, void *data, long long index)
{
	t_rb_tree	*t;

	if (!*root)
	{
		*root = rb_node_create(data, index, NULL);
		return (0);
	}
	t = *root;
	while (1)
	{
		if (index > t->index && t->right)
			t = t->right;
		else if (index < t->index && t->left)
			t = t->left;
		else
			break;
	}
	if (index == t->index)
		return (1);
	if (index > t->index)
	{
		t->right = rb_node_create(data, index, t);
		t = t->right;
	}
	else if (index < t->index)
	{
		t->left = rb_node_create(data, index, t);
		t = t->left;
	}
	rb_balance(root, t);
	return (1);
}
