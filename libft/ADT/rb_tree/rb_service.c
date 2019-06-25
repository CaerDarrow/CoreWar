/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_service.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 19:09:58 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/20 16:22:33 by jjacobso         ###   ########.fr       */
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

void			rb_set_left(t_rb_tree *t, t_rb_tree *l)
{
	if (t)
	{
		t->left = l;
		if (l)
			l->parent = t;
	}
}

void			rb_set_right(t_rb_tree *t, t_rb_tree *r)
{
	if (t)
	{
		t->right = r;
		if (r)
			r->parent = t;
	}
}

void			rb_rotate_left(t_rb_tree *tr)
{
	// ft_printf("\nBEFORE LEFT ROTATE:\n");
	// rb_print(tr, 1);
	if (!tr || !tr->right)
		return ;
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
	// ft_printf("\nAFTER LEFT ROTATE:\n");
	// rb_print(tr, 1);
}

void			rb_rotate_right(t_rb_tree *tr)
{
	// ft_printf("\nBEFORE RIGHT ROTATE:\n");
	// rb_print(tr, 1);
	if (!tr || !tr->left)
		return ;
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
	// ft_printf("\nAFTER RIGHT ROTATE:\n");
	// rb_print(tr, 1);
}

t_rb_tree	*rb_left(t_rb_tree *t)
{
	return (t ? t->left : NULL);
}

t_rb_tree	*rb_right(t_rb_tree *t)
{
	return (t ? t->right : NULL);
}

t_rb_tree	*rb_parent(t_rb_tree *t)
{
	return (t ? t->parent : NULL);
}

int			rb_is_red(t_rb_tree *t)
{
	return (t ? t->clr == R : 0);
}

void			rb_fix_insertion(t_rb_tree *t)
{
	t_rb_tree	*uncle;
	t_rb_tree	*gr;
(void)gr;
	//rm
	// if (t == *root)
	// {
	// 	t->clr = B;
	// 	return ;
	// }
	//
	while (rb_is_red(rb_parent(t)))
	{
		if (rb_parent(t) == rb_left(rb_grandparent(t)))
		{
			if (rb_is_red(uncle = rb_uncle(t)))
			{
				uncle->clr = B;
				t->parent->clr = B;
				t = rb_grandparent(t);
				t->clr = R;
			}
			else
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
		}
		else
		{
			if (rb_is_red(uncle = rb_uncle(t)))
			{
				uncle->clr = B;
				t->parent->clr = B;
				t = rb_grandparent(t);
				t->clr = R;
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
}

void			rb_fix_root(t_rb_tree **root)
{
	while((*root)->parent)
		(*root) = (*root)->parent;
	(*root)->clr = B;
}
