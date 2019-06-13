/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_apply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 15:36:01 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/13 19:11:51 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			rb_nrl(t_rb_tree **root, void (*f)(t_rb_tree **))
{
	if (*root)
	{
		f(root);
		rb_nrl(&(*root)->left, f);
		rb_nrl(&(*root)->right, f);
	}
}

void			rb_rnl(t_rb_tree **root, void (*f)(t_rb_tree **))
{
	if (*root)
	{
		rb_rnl(&(*root)->right, f);
		f(root);
		rb_rnl(&(*root)->left, f);
	}
}

void			rb_rln(t_rb_tree **root, void (*f)(t_rb_tree **))
{
	if (*root)
	{
		rb_rnl(&(*root)->right, f);
		rb_rnl(&(*root)->left, f);
		f(root);
	}
}
