/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:45:35 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/11 17:41:24 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "op.h"
# include "libft.h"

/*
** read
*/

char				*read_s(char *fname);

/*
** parse (lexer)
*/

# define I i + g_readed

typedef struct		s_token
{
	int				pos[2];
	int				type;
	char			*token;
}					t_token;

int					islabelchar(char c);
t_token				*inittoken(int strpos, int type);
void				get_sep(char *rd, int *i, t_list **lst);
void				get_commandname(char *rd, int *i, t_list **lst);
void				get_string(char *rd, int *i, t_list **lst);
void				get_comment(char *rd, int *i, t_list **lst);
void				get_direct(char *rd, int *i, t_list **lst);
void				get_label(char *rd, int *i, t_list **lst);
t_list				*parse(char *rd);

int					g_readed;
int					g_line;

enum				e_type {
	SEP, COMMAND_NAME, STRING, LABEL, COMMENT, DIRECT, DIRECT_LABEL,
	INSTRUCTION, REGISTER, INDERECT, NEWLINE
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

int					syntax(t_list *lst);

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
