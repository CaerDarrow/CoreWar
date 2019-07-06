/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_service.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:09:57 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/06 18:16:50 by jjacobso         ###   ########.fr       */
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
	else
		cursor->cycles_to_exec = 0;
}

void			print_usage(void)
{
	ft_printf("Usage:\n"
	"\t-a\t: Prints output from \"aff\" (Default is to hide it)\n"
	"#### TEXT OUTPUT MODE ##################################################\n"
	"\t-d N\t: Dumps memory (x64 mode) after N cycles then exits\n"
	"\t-dump N\t: Dumps memory (x32 mode) after N cycles then exits\n"
	"\t-n N\t: Sets the number of the next player\n"
	"\t-v N\t: Verbosity levels, can be added together to enable several\n"
	"\t\t* 2 : Show cycles\n"
	"\t\t* 4 : Show operations\n"
	"\t\t* 8 : Show deaths\n"
	"\t\t* 16 : Show cursors movements\n"
	"#### OUTPUT MODE #######################################################\n"
	"\t-vis N\t: Turn on visualisator and/or set size of cell\n"
	"\t\t* N in range [1, 18] or not defined; (18 is warcraft mode)\n");
}
