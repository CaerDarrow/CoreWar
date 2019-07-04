/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:49:55 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/04 20:13:29 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "op.h"

# define BYTE(n)		n
# define XOR(x, y)		(x ^ y)
# define PAIR(x, y)		((t_pair){x, y})
# define REG_NUM		16
# define VERBOSE_LVL(n)	(g_verbose & n)
# define RAW_ARG(n)		get_rawarg(argv, argc, n, g_op_tab[cursor->op_code].dir)
# define CURSOR(x)		 ((t_cursor*)x->data)

typedef unsigned char	t_uchar;

typedef struct			s_cursor
{
	char				id;
	long long			index;
	t_uchar				reg[REG_NUM][REG_SIZE];
	char				carry;
	int					last_live_call;
	t_uchar				op_code;
	int					cycles_to_exec;
	int					position;
}						t_cursor;

typedef struct			s_game_entity
{
	t_uchar				*bg;
	t_list				*cursors;
	t_list				*players;
	char				n_players;
	long				cycle;
	int					cycles_to_die;
	int					periods_with_same_ctd;
	int					last_alive_player;
	int					last_check;
	int					live_calls;
	int					alive_cursors;
	char				print_aff;
}						t_game_entity;

typedef struct			s_op
{
	char				*name;
	char				argc;
	char				*argv;
	char				index;
	int					cycles;
	void				(*op)(t_game_entity *, t_cursor *,
						t_uchar, t_list *);
	char				argtypes;
	char				dir;
}						t_op;

int						g_verbose;
int						g_dump_flag;
int						g_d_flag;
t_op					g_op_tab[17];

/*
**						error.c
*/
void					error(char *s);
void					champ_error(char *s, int player);
/*
**						get_header.c
*/
unsigned int			get_magic(int fd, int cur_player);
void					get_prog_name(int fd, char s[], int cur_player);
unsigned int			get_prog_size(int fd, int cur_player);
void					get_comment(int fd, char s[], int cur_player);
t_uchar					*get_code(int fd, unsigned int size, int cur_player);
/*
**						reader.c
*/
int						get_null(int fd);
void					read_champs(int a, const char *arg[], t_game_entity *g);
/*
**						game.c
*/
void					game_loop(t_game_entity *entity);
/*
**						op_source_1.c
*/
void					live(t_game_entity *entity, t_cursor *cursor,
							t_uchar argc, t_list *argv);
void					ld(t_game_entity *entity, t_cursor *cursor,
							t_uchar argc, t_list *argv);
void					st(t_game_entity *entity, t_cursor *cursor,
							t_uchar argc, t_list *argv);
void					add(t_game_entity *entity, t_cursor *cursor,
							t_uchar argc, t_list *argv);
void					sub(t_game_entity *entity, t_cursor *cursor,
							t_uchar argc, t_list *argv);
/*
**						op_source_2.c
*/
void					and(t_game_entity *entity, t_cursor *cursor,
							t_uchar argc, t_list *argv);
void					or(t_game_entity *entity, t_cursor *cursor,
							t_uchar argc, t_list *argv);
void					xor(t_game_entity *entity, t_cursor *cursor,
							t_uchar argc, t_list *argv);
void					zjmp(t_game_entity *entity, t_cursor *cursor,
							t_uchar argc, t_list *argv);
void					ldi(t_game_entity *entity, t_cursor *cursor,
							t_uchar argc, t_list *argv);
/*
**						op_source_3.c
*/
void					sti(t_game_entity *entity, t_cursor *cursor,
							t_uchar argc, t_list *argv);
void					clone(t_game_entity *entity, t_cursor *cursor,
							t_uchar argc, t_list *argv);
void					lld(t_game_entity *entity, t_cursor *cursor,
							t_uchar argc, t_list *argv);
void					lldi(t_game_entity *entity, t_cursor *cursor,
							t_uchar argc, t_list *argv);
void					lclone(t_game_entity *entity, t_cursor *cursor,
							t_uchar argc, t_list *argv);
/*
**						op_source_4.c
*/
void					aff(t_game_entity *entity, t_cursor *cursor,
							t_uchar argc, t_list *argv);
/*
**						op_service_1.c
*/
t_uchar					get_dir_size(t_uchar op_code);
void					set_carry(char *carry, int num);
int						get_arg_size(t_uchar argc, int flag, int n);
int						uchar_to_int(t_uchar *s, int size);
/*
**						op_service_2.c
*/
int						get_rawarg(t_list *argv, int argc, int n, int flag);
int						get_num_by_addr(unsigned char *bg, int addr, int size);
int						arg_code(t_uchar argc, int n);
int						get_arg(t_uchar *bg, t_cursor *c, int arg, int code);
/*
**						game_service.c
*/
int						correct_position(int new_pos);
void					set_op_code(t_cursor *cursor, t_uchar *bg);
/*
**						game_validiation.c
*/
int						is_valid_reg(int n);
int						is_valid_op(char op_code);
int						is_live_op(char op_code);
int						is_valid_argc(t_uchar argc, int op_code);
int						is_proper_argc(t_uchar argc, int op_code);
int						is_valid_player(t_game_entity *game, int p);
/*
**						read_args.c
*/
int						read_reg_value(t_list **res, t_uchar *bg, t_cursor *c,
							int *offset);
void					read_ind_value(t_list **res, t_uchar *bg, t_cursor *c,
							int *offset);
void					read_dir_value(t_list **res, t_uchar *bg, t_cursor *c,
							int *offset);
/*
**						registers.c
*/
void					set_reg_num(t_cursor *cursor, int n, int value);
t_uchar					*get_reg_num(t_cursor *cursor, int n);
/*
**						print_data.c
*/
void					print_bg(t_game_entity *entity, int mod);
/*
**						apply_op.c
*/
int						apply_op(t_game_entity *entity, t_cursor *cursor);
/*
**						check.c
*/
void					check_cursors(t_game_entity *entity);
/*
**						cursor.c
*/
void					copy_reg(t_uchar dest[REG_NUM][REG_SIZE],
							t_uchar src[REG_NUM][REG_SIZE]);
void					destroy_cur(t_list **t);
int						cursor_should_die(t_cursor *c, t_game_entity *entity);
void					move_cursor(t_cursor *cursor, int b);
t_cursor				*cursor_create(t_game_entity *entity, int id);
/*
**						set_flags.c
*/
int						set_flags(int argc, const char *argv[],
							t_game_entity *entity, int *i);
/*
** C="test.cor";
** make corewar && ./corewar -v 14  $C > t;./vm_champs/corewar -v 14 $C > tt;
** diff t tt | head -n 50
*/
#endif
