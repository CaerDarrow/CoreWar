/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:13:33 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/19 16:33:09 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				is_valid_reg(int n)
{
	return (n > 0 && n <= 16);
}

int				is_valid_op(char op_code)
{
	return (op_code > 0 && op_code <= 16);
}

int				is_live_op(char op_code)
{
	return (op_code == 1);
}

int				is_proper_argc(t_uchar argc, int op_code)
{
	int					i;
	int					type;
	int					code;

	i = -1;
	while (++i < g_op_tab[op_code].argc)
	{
		type = g_op_tab[op_code].argv[i];
		code = (argc >> (6 - i * 2)) & 0b11;
		if (!(((type & T_DIR) && (code == DIR_CODE)) ||
			((type & T_IND) && (code == IND_CODE)) ||
			((type & T_REG) && (code == REG_CODE))))
			return (0);
	}
	return (1);
}

int				is_valid_argc(t_uchar argc, int op_code)
{
	int					i;
	int					code;

	i = -1;
	while (++i < g_op_tab[op_code].argc)
	{
		code = (argc >> (6 - i * 2)) & 0b11;
		if (!((code == DIR_CODE) ||
			(code == IND_CODE) ||
			(code == REG_CODE)))
			return (0);
	}
	return (1);
}

int				is_valid_player(t_game_entity *game, int p)
{
	return (ft_inrange(p, 1, l_size(game->players)));
}
