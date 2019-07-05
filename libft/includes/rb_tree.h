/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:39:00 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/28 16:10:47 by jjacobso         ###   ########.fr       */
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
	int						index;
	void					*data;
};

/*
**							rb_add.c
*/
int							rb_push(t_rb_tree **t, void *data, int index);
t_rb_tree					*rb_node_create(void *data, int index,
								t_rb_tree *parent);
/*
**							rb_apply.c
*/
void						rb_nrl(t_rb_tree **t, void (*f)(t_rb_tree **));
void						rb_rnl(t_rb_tree **root, void (*f)(t_rb_tree **));
void						rb_rln(t_rb_tree **root, void (*f)(t_rb_tree **));
/*
**							rb_get.c
*/
int							rb_size(t_rb_tree *t);
t_rb_tree					*rb_grandparent(t_rb_tree *t);
t_rb_tree					*rb_uncle(t_rb_tree *t);
t_rb_tree					*rb_find(t_rb_tree *t, int index);
t_rb_tree					*rb_parent(t_rb_tree *t);
/*
**							rb_service.c
*/
void						rb_backtrack(t_rb_tree **root);
t_rb_tree					*rb_left(t_rb_tree *t);
t_rb_tree					*rb_right(t_rb_tree *t);
int							rb_is_red(t_rb_tree *t);
void						rb_set_left(t_rb_tree *t, t_rb_tree *l);
void						rb_set_right(t_rb_tree *t, t_rb_tree *r);
int							rb_set_parent_link(t_rb_tree *t, t_rb_tree *ptr);
void						rb_print(t_rb_tree *t);
int							rb_is_black(t_rb_tree *t);
/*
**							rb_remove.c
*/
int							rb_remove(t_rb_tree **root, int index,
								void (*f)(void *));
void						rb_destroy(t_rb_tree **root, void (*f)(void *));
void						rb_destroy_node(t_rb_tree **t, void (*f)(void *));
/*
**							rb_rotate.c
*/
void						rb_rotate_left(t_rb_tree *t);
void						rb_rotate_right(t_rb_tree *t);
#endif
