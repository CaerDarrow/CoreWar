/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 14:43:07 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/28 14:43:18 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			rb_rotate_left(t_rb_tree *tr)
{
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
}

void			rb_rotate_right(t_rb_tree *tr)
{
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
}
