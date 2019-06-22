/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_num_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 17:41:54 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 17:41:56 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			get_num_player(t_game_entity *entity, int x, int y)
{
	const int num_pixel = get_num_pixel(entity, x, y);

	if (ft_memcmp(WIN->data + num_pixel, PICTURES.player1,
			sizeof(int) * SIDE_SQUARE) == 0)
		return (0);
	if (ft_memcmp(WIN->data + num_pixel, PICTURES.player2,
			sizeof(int) * SIDE_SQUARE) == 0)
		return (1);
	if (ft_memcmp(WIN->data + num_pixel, PICTURES.player3,
			sizeof(int) * SIDE_SQUARE) == 0)
		return (2);
	if (ft_memcmp(WIN->data + num_pixel + SIZE_FIELD_X,
			PICTURES.player4 + SIDE_SQUARE, sizeof(int) * SIDE_SQUARE) == 0)
		return (3);
	return (4);
}
