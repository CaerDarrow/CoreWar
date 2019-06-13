/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_service.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 19:09:58 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/13 19:50:57 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		rb_print(t_rb_tree *t, int iter)
{
	if (t)
	{
		iter += 2;
		rb_print(t->right, iter);
		if (t->clr == R)
			ft_printf(RED"%*d\n"RESET, iter + 2, *(int*)t->data);
		else
			ft_printf("%*d\n", iter + 2, *(int*)t->data);
		rb_print(t->left, iter);
	}
}

void			rb_rotate_left(t_rb_tree **root)
{
	t_rb_tree	*tr;

	if (!*root || !(*root)->right)
		return ;
	tr = *root;
	if (tr->parent)
	{
		if (tr->parent->left == tr)
			tr->parent->left = tr->right;
		else
			tr->parent->right = tr->right;
		tr->right->parent = tr->parent;
	}
	else
		tr->right->parent = NULL;
	tr->parent = tr->right;
	tr->right = tr->parent->left;
	tr->parent->left = tr;
	if (tr->right)
		tr->right->parent = tr;
	(*root) = tr->parent;
}

void			rb_rotate_right(t_rb_tree **root)
{
	t_rb_tree	*tr;

	if (!*root || !(*root)->left)
		return ;
	tr = *root;
	if (tr->parent)
	{
		if (tr->parent->left == tr)
			tr->parent->left = tr->left;
		else
			tr->parent->right = tr->left;
		tr->left->parent = tr->parent;
	}
	else
		tr->left->parent = NULL;
	tr->parent = tr->left;
	tr->left = tr->parent->right;
	tr->parent->right = tr;
	if (tr->left)
		tr->left->parent = tr;
	(*root) = tr->parent;
}


void			rb_balance(t_rb_tree **root, t_rb_tree *t)
{
	(void)t;(void)root;
	// t_rb_tree	*uncle;
	//
	// while (t->parent->clr == B)
	// {
	// 	uncle = rb_uncle(child);
	// 	if (uncle && uncle->clr == R)
	// 	{
	// 		uncle->clr = B;
	// 		child->parent->clr = B;
	// 		t = rb_grandparent(t);
	// 		t->clr = R;
	// 	}
	// 	else
	// 	{
	// 		if (t == t->parent->left)
	// 		{
	//
	// 		}
	// 		else
	// 		{
	//
	// 		}
	// 	}
	// }
	// (*root)->clr = B;
}
