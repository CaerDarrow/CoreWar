/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:45:35 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/03 19:47:39 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "op.h"
# include "libft.h"

typedef struct		s_unit
{
	t_header		header;
	unsigned char	exec[];
}					t_unit;

/*
** parse(lexer)
*/

# define I i + g_readed

typedef struct		s_token
{
	int				pos[3];
	int				type;
	int				argsize;
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
	COMMAND_NAME,
	REGISTER,
	DIRECT,
	COMMENT,
	INDIRECT,
	INSTRUCTION,
	SEP,
	STRING,
	LABEL,
	NEWLINE,
	DIRECT_LABEL,
	INDIRECT_LABEL = 12
};

/*
** syntax/encode
*/

# define TOK ((t_token *)(*lst)->data)
# define TOKEN ((t_token *)(*lst)->data)->token
# define TTYPE ((t_token *)(*lst)->data)->type

typedef struct		s_op
{
	char			*name;
	int				argc;
	t_arg_type		*argv;
	int				index;
	int				cycles;
	char			*comment;
	int				argtypes;
	int				t_dirsize;
}					t_op;

t_op				g_op_tab[17];

void				check_comment(t_list **lst);
void				check_command(t_list **lst);
void				check_label(t_list **lst);
void				check_instruction(t_list **lst);
void				check_newline(t_list **lst);
t_op				*check_opname(t_list **lst);
int					syntax(t_list **lst);
void				translate_labels(t_list **lst);
t_unit				*encodechamp(t_list **lst, size_t psize);
unsigned char		*encode(t_list **lst, size_t psize);
void				printtoken(t_list **parsed);

enum				e_error_code {
	SYNTAX,
	NAMELEN,
	COMMENTLEN,
	ARG,
	LBL
};

typedef struct		s_label
{
	char			*name;
	int				pos;
}					t_label;

void				c_error(t_list **lst, char err);

/*
** write/read
*/

char				*read_s(char *fname);
void				set_magic(t_unit *unit);
void				set_name(char *name, t_unit *unit);
void				set_prog_size(int size, t_unit *unit);
void				set_comment_name(char *name, t_unit *unit, char *token);
void				set_exec(unsigned char *exec, int size, t_unit *unit);
void				writechamp(t_unit *unit, char *fname);

#endif
