/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:39:00 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/15 19:27:17 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_H

# define RB_TREE_H

typedef enum {B, R}			t_color;

typedef struct s_rb_tree	t_rb_tree;//set

struct						s_rb_tree
{
	t_rb_tree				*right;
	t_rb_tree				*left;
	t_rb_tree				*parent;
	t_color					clr;
	long long				index;
	void					*data;
};

int							rb_size(t_rb_tree *t);
void						rb_remove(t_rb_tree *t);
t_rb_tree					*rb_node_create(void *data, long long index,
								t_rb_tree *parent);
int							rb_push(t_rb_tree **t, void *data, long long index);
void						rb_nrl(t_rb_tree **t, void (*f)(t_rb_tree **));
void						rb_rnl(t_rb_tree **root, void (*f)(t_rb_tree **));
void						rb_rln(t_rb_tree **root, void (*f)(t_rb_tree **));
t_rb_tree					*rb_grandparent(t_rb_tree *t);
t_rb_tree					*rb_uncle(t_rb_tree *t);
void						rb_rotate_left(t_rb_tree *t);
void						rb_rotate_right(t_rb_tree *t);
void						rb_print(t_rb_tree *t, int i);
void						rb_fix_insertion(t_rb_tree *t);
void						rb_fix_root(t_rb_tree **root);
void						*rb_find(t_rb_tree *t, int index);
#endif
