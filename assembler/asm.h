/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:45:35 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/04 17:55:18 by ajon-hol         ###   ########.fr       */
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

typedef struct		s_parsed
{
	char			*label;
	char			*instruction;
	char			*reg;
	char			*separator;
	char			*direct;
	char			*direct_label;
	char			*string;
}					t_parsed;

int					read_s(char *fname);
int					parse(char *readed);
t_unit				*initchamp(void);
void				writechamp(t_unit *unit, char *fname);
void				set_magic(t_unit *unit);
void				set_name(char *name, t_unit *unit);
void				set_prog_size(int size, t_unit *unit);
void				set_comment(char *comment, t_unit *unit);
void				set_exec(unsigned char *exec, int size, t_unit *unit);

t_op				g_op_tab[17];	
#endif
