/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_service.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:09:57 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/13 18:22:31 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				correct_position(int new_pos)
{
	while (new_pos < 0)
		new_pos += MEM_SIZE;
	new_pos %= MEM_SIZE;
	return (new_pos);
}

static t_uchar	get_op_code(t_cursor *cursor, t_uchar *bg)
{
	return (bg[cursor->position]);
}

void			set_op_code(t_cursor *cursor, t_uchar *bg)
{
	cursor->op_code = get_op_code(cursor, bg);
	if (is_valid_op(cursor->op_code))
		cursor->cycles_to_exec = g_op_tab[cursor->op_code].cycles;
}
