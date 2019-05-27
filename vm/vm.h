/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:49:55 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/24 21:58:44 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include			"libft.h"
# include			"op.h"

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

void				read_champs(int ac, const char *argv[], t_game_entity *ge);
void				error(char *s);
void				game_loop(t_game_entity *entity);
#endif
