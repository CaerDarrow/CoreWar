/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:57:32 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/26 13:09:49 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			rb_set_parent_link(t_rb_tree *t, t_rb_tree *ptr)
{
	if (!t || !t->parent)
		return (0);
	if (t->parent->left == t)
		rb_set_left(t->parent, ptr);
	else
		rb_set_right(t->parent, ptr);
	return (1);
}

int				rb_n_childs(t_rb_tree *t)
{
	if (!t)
		return (-1);
	return ((t->left ? 1 : 0) + (t->right ? 1 : 0));
}

void			rb_destroy_node(t_rb_tree **t, void (*f)(void *))
{
	f((*t)->data);
	ft_memdel((void**)t);
}

// int				rb_remove_root(t_rb_tree **root, void (*f)(void *))
// {
// 	t_rb_tree	*next;
//
// 	if (rb_n_childs(*root) == 2)
// 		next = rb_next(*root);
// 	else if (rb_n_childs(*root) == 1)
// 	{
// 		if ((*root)->left)
// 			next = (*root)->left;
// 		else
// 			next = (*root)->right;
// 	}
// 	else
// 		next = 0;
// 	rb_destroy_node(root, f);
// 	*root = next;
// }


int				rb_remove(t_rb_tree **root, int index, void (*f)(void *))
{
	(void)root;
	(void)index;
	(void)f;
	return (0);
	// t_rb_tree	*t;
	// t_rb_tree	*next;
	//
	//
	// if (!(t = rb_find(*root, index)))
	// 	return (0);
	// if (*t == root)
	// 	rb_remove_root(root, f);
	// else
	// {
	// 	if (rb_n_childs(t) == 0)
	// 	{
	// 		rb_set_parent_link(t, NULL);
	// 		rb_destroy_node(&t, f);
	// 	}
	// 	else if (rb_n_childs(t) == 1)
	// 	{
	// 		if (t->left)
	// 			rb_set_parent_link(t, t->left);
	// 		else
	// 			rb_set_parent_link(t, t->right);
	// 		rb_destroy_node(&t, f);
	// 	}
	// 	else if (rb_n_childs(t) == 2)
	// 	{
	// 		rb_set_parent_link(t, (next = rb_next(t)));
	// 		rb_set_left(next, t->left);
	// 		rb_destroy_node(&t, f);
	// 	}
	// }

}
