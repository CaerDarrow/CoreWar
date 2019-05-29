/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:49:55 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/29 21:18:03 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include			"libft.h"
# include			"op.h"

# define BYTE(n)	n

typedef struct		s_cursor
{
	char			**reg;
	char			carry;
	int				last_live_call;
	int				op_code;
	int				cycles_to_exec;
	int				cur_pos;
	int				step;
}					t_cursor;

typedef struct		s_game_entity
{
	unsigned char	*bg;
	t_list			*cursors;
	t_list			*players;
	char			n_players;
	long			cycle;
	int				cycles_to_die;
	int				cycles_with_same_ctd;
	int				last_alive_player;
}					t_game_entity;

void				read_champs(int ac, const char *argv[], t_game_entity *ge);
void				game_loop(t_game_entity *entity);
/*
**					error.c
*/
void				error(char *s);
void				champ_error(char *s, int player);
/*
**					get_header.c
*/
int					get_null(int fd);
unsigned int		get_magic(int fd, int cur_player);
void				get_prog_name(int fd, char s[], int cur_player);
unsigned int		get_prog_size(int fd, int cur_player);
void				get_comment(int fd, char s[], int cur_player);
unsigned char		*get_code(int fd, unsigned int size, int cur_player);

void				init_cursors(t_game_entity *entity);
int					time_to_apply_func(t_game_entity *entity, t_cursor *cursor);
int					apply_func(t_game_entity *entity, t_cursor *cursor);
int					is_valide(int func_code);
int					is_live_func(int func_code);
void				move_cursor(t_game_entity *entity, t_cursor *curso);
void				shift_cycle(t_cursor *cursor);
void				check_handler(t_game_entity *entity, int *live_calls);

void				destroy_cur(t_list **t);
void				set_reg_num(t_cursor *c, int n, int value);
void				destroy_cursors(t_game_entity *entity);
int					cursor_should_die(t_list *c, int cycles_to_die);
void				move_cursor(t_game_entity *entity, t_cursor *cursor);
void				shift_cycle(t_cursor *cursor);
t_cursor			*cursor_create(int id);
/*
**	TODO
**	Game progress in procents
*/
#endif
