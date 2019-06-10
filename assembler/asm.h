/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:45:35 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/10 19:52:23 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "op.h"
# include "libft.h"
# define I i + g_readed

/*
** read
*/

char				*read_s(char *fname);

/*
** parse (lexer)
*/

typedef struct		s_parsed
{
	int				tokpos[2];
	char			*toktype;
	char			*token;
}					t_parsed;

int					islabelchar(char c);
void				get_sep(char *rd, int *i);
void				get_commandname(char *rd, int *i);
void				get_string(char *rd, int *i);
void				get_comment(char *rd, int *i);
void				get_direct(char *rd, int *i);
void				get_label(char *rd, int *i);
int					parse(char *readed);

int					g_readed;
int					g_line;

static void			(*g_get[6])(char *rd, int *i) = {
	get_sep,
	get_commandname,
	get_string,
	get_label,
	get_comment,
	get_direct
};

enum				e_get {
	SEP, COMMAND_NAME, STRING, LABEL, COMMENT, DIRECT
};

/*
** syntax
*/

typedef struct		s_op
{
	char			*name;
	int				argc;
	int				*argv;
	int				index;
	int				cycles;
	char			*comment;
	int				argtypes;
	int				t_dirsize;
}					t_op;

t_op				g_op_tab[17];

/*
** write
*/

typedef struct		s_unit
{
	t_header		header;
	unsigned char	exec[];
}					t_unit;

void				set_magic(t_unit *unit);
void				set_name(char *name, t_unit *unit);
void				set_prog_size(int size, t_unit *unit);
void				set_comment(char *comment, t_unit *unit);
void				set_exec(unsigned char *exec, int size, t_unit *unit);
t_unit				*initchamp(void);
void				writechamp(t_unit *unit, char *fname);

/*
** garbage
*/

int					match(char *regexp, char *text);
int					matchstar(int c, char *regexp, char *text);
int					matchhere(char *regexp, char *text);
char				*lexer(char *s, const char *delim, char **save_ptr);

#endif
