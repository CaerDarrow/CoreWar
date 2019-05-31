/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:49:55 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/31 16:23:23 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include			"libft.h"
# include			"op.h"

# define BYTE(n)	n

typedef struct		s_cursor
{
	unsigned char	**reg;
	char			carry;
	int				last_live_call;
	unsigned char	op_code;
	int				cycles_to_exec;
	int				position;
	char			step;//dont need to store
	char			moved;
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

typedef struct					op_s
{
	char 						*name;
	int							argc;
	int							*argv;
	int							index;
	int							cycles;
	char						*comment;
	int							argtypes;
	int							t_dirsize;
}								t_op;

t_op							g_op_tab[17];
void							(*g_op_ptr[17])(t_game_entity *, t_cursor *,
								unsigned char, unsigned char *);

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
int					time_to_apply_op(t_cursor *cursor);
int					apply_op(t_game_entity *entity, t_cursor *cursor);
int					is_valide_op(char op_code);
int					is_live_op(char op_code);
void				check_handler(t_game_entity *entity, int *live_calls);

void				destroy_cur(t_list **t);
void				set_reg_num(t_cursor *c, int n, int value);
void				destroy_cursors(t_game_entity *entity);
int					cursor_should_die(t_list *c, int cycles_to_die);
void				move_cursor(t_cursor *cursor, int b);
void				shift_cycle(t_cursor *cursor);
t_cursor			*cursor_create(int id, char playes);
void				live(t_game_entity * entity, t_cursor *cursor,
unsigned char argc, unsigned char *argv);
/*
TODO: move if invalid func args or all valide;
all funcs implementation;
welcome,goodbye messages;
flag managment;
set\get reg
**	Features:
**	Game progress in procents
** test.cor 156018 cycles;
*/
#endif
