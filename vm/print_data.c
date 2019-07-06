/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:39:07 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/06 16:52:25 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			print_bg(t_game_entity *entity, int mod)
{
	int			i;
	int			offset;

	offset = 0;
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i % mod == 0)
		{
			PRINT("0x%04x : ", offset);
			offset += mod;
		}
		PRINT("%02x ", entity->bg[i]);
		if (i % mod == mod - 1)
			PRINT("\n");
	}
}

void			print_n_cells_after(t_uchar *bg, int position, int bytes)
{
	int			i;

	i = -1;
	while (++i < bytes)
	{
		PRINT("%.2x ", bg[correct_position(position + i)]);
	}
	write(1, "\n", 1);
}
