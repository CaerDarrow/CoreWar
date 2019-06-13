/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:48:37 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/13 19:14:59 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				rb_size(t_rb_tree *t)
{
	int			i;

	i = 0;
	if (t)
	{
		i += rb_size(t->right) + 1;
		i += rb_size(t->left);
	}
	return (i);
}

t_rb_tree		*rb_grandparent(t_rb_tree *t)
{
	if (t && t->parent)
		return (t->parent->parent);
	return (NULL);
}

t_rb_tree		*rb_uncle(t_rb_tree *t)
{
	t_rb_tree	*gp;

	gp = rb_grandparent(t);
	if (gp)
	{
		if (gp->left == t)
			return (gp->right);
		return (gp->left);
	}
	return (NULL);
}
