/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:49:55 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/28 16:27:29 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include			"libft.h"
# include			"op.h"

# define BYTE(n)	n
# define UINT_SIZE	8

typedef struct		s_cursor
{
	char			**reg;
	char			carry;
	int				last_live_call;
	int				last_player_called;
	int				op_code;
	int				cycles_to_exec;
	int				cur_pos;
	int				step;
}					t_cursor;

typedef struct		s_game_entity
{
	unsigned char	*bg;
	t_list			*cursor;
	t_list			*player;
	char			players;
}					t_game_entity;

typedef struct		s_unit
{
	t_header		header;
	unsigned char	*exec;
}					t_unit;

void				read_champs(int ac, const char *argv[], t_game_entity *ge);
void				game_loop(t_game_entity *entity);
/*
**					error.c
*/
void				error(char *s);
/*
**					get_header.c
*/
int					get_null(int fd);
unsigned int		get_magic(int fd);
void				get_prog_name(int fd, char s[]);
unsigned int		get_prog_size(int fd);
void				get_comment(int fd, char s[]);
unsigned char		*get_code(int fd, unsigned int size);

#endif
