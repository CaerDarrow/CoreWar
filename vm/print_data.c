/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:39:07 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/04 17:42:31 by jjacobso         ###   ########.fr       */
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
			ft_printf("0x%04x : ", offset);
			offset += mod;
		}
		ft_printf("%02x ", entity->bg[i]);
		if (i % mod == mod - 1)
			ft_printf("\n");
	}
}
