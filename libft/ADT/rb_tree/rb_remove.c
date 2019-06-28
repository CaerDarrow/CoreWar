/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:57:32 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/28 14:49:20 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			rb_destroy_node(t_rb_tree **t, void (*f)(void *))
{
	f((*t)->data);
	ft_memdel((void**)t);
}

void			rb_destroy(t_rb_tree **root, void (*f)(void *))
{
	if (*root)
	{
		rb_destroy(&(*root)->right, f);
		rb_destroy(&(*root)->left, f);
		rb_destroy_node(root, f);
	}
}

static t_rb_tree		*rb_successor(t_rb_tree *t)
{
	t_rb_tree	*b;

	if (t->right)
	{
		t = t->right;
		while (t && t->left)
			t = t->left;
		return (t);
	}
	b = t->parent;
	while (b && t == b->right)
	{
		t = b;
		b = b->parent;
	}
	return (b);
}

static void			rb_move_node(t_rb_tree **from, t_rb_tree *to, void (*f)(void *))
{
	f(to->data);
	to->index = (*from)->index;
	to->data = (*from)->data;
	ft_memdel((void**)from);
}

static void			rb_fix_remove(t_rb_tree *t)
{
	(void)t;
}

int				rb_remove(t_rb_tree **root, int index, void (*f)(void *))
{
	t_rb_tree	*node;
	t_rb_tree	*temp;
	t_rb_tree	*successor;
	t_color		clr;

	if (!(node = rb_find(*root, index)))
		return (0);
	successor = (!node->left || !node->right) ? node : rb_successor(node);
	temp = (successor->left) ? successor->left : successor->right;
	if (!successor->parent)
	{
		if (temp)
			temp->parent = NULL;
		*root = temp;
	}
	else
		rb_set_parent_link(successor, temp);
	clr = successor->clr;
	if (successor != node)
		rb_move_node(&successor, node, f);
	else
		rb_destroy_node(&successor, f);
	if (clr == B)
		rb_fix_remove(temp);
	return (1);
}
