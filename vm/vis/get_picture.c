/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_picture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 17:42:47 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 17:42:49 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	*get_picture(t_game_entity *entity, int num_player)
{
	int num;

	if (num_player == 0)
		return (PICTURES.player1);
	if (num_player == 1)
		return (PICTURES.player2);
	if (num_player == 2)
		return (PICTURES.player3);
	if (num_player == 3)
		return (PICTURES.player4);
	return (NULL);
}
