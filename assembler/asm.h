/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:45:35 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/05/28 16:03:30 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "op.h"
# include "libft.h"

typedef struct	s_unit
{
	header_t	header;
	char		exec[CHAMP_MAX_SIZE];
}				t_unit;

t_unit			*initchamp(void);
void			writechamp(t_unit *unit, char *filename);
void			set_magic(t_unit *unit);
void			set_name(char *name, t_unit *unit);
void			set_prog_size(int size, t_unit *unit);
void			set_comment(char *comment, t_unit *unit);

#endif
