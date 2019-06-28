/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:46:15 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/28 14:41:55 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_rb_tree			*rb_node_create(void *data, int index, t_rb_tree *parent)
{
	t_rb_tree		*tr;

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
		tr->clr = R;
	return (tr);
}

static void			rb_fix_insert(t_rb_tree *t)
{
	t_rb_tree	*uncle;
	t_rb_tree	*gr;

	while (rb_is_red(rb_parent(t)))
	{
		if (rb_is_red(uncle = rb_uncle(t)))
		{
			uncle->clr = B;
			t->parent->clr = B;
			t = rb_grandparent(t);
			t->clr = R;
		}
		else if (rb_parent(t) == rb_left(rb_grandparent(t)))
		{
			if (t == rb_right(rb_parent(t)))
			{
				t = t->parent;
				rb_rotate_left(t);
			}
			t->parent->clr = B;
			if ((gr = rb_grandparent(t)))
			{
				gr->clr = R;
				rb_rotate_right(gr);
			}
		}
		else
		{
			if (t == rb_left(rb_parent(t)))
			{
				t = t->parent;
				rb_rotate_right(t);
			}
			t->parent->clr = B;
			if ((gr = rb_grandparent(t)))
			{
				gr->clr = R;
				rb_rotate_left(gr);
			}
		}
	}
}

int				rb_push(t_rb_tree **root, void *data, int index)
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
	rb_fix_insert(t);
	rb_backtrack(root);
	return (1);
}
