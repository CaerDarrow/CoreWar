/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 18:08:48 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 18:09:08 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	*get_player1(t_visualizer *vis)
{
	int	*color_field;

	if (SIDE_SQUARE == WARCRAFT_SQUARE)
		return (get_horde());
	if (!(color_field = (int *)malloc(sizeof(int) * SIDE_SQUARE * SIDE_SQUARE)))
		error("Malloc error");
	ft_intset(color_field, PLAYER_1, SIDE_SQUARE * SIDE_SQUARE);
	return (color_field);
}

int	*get_player2(t_visualizer *vis)
{
	int	*color_field;

	if (SIDE_SQUARE == WARCRAFT_SQUARE)
		return (get_alliance());
	if (!(color_field = (int *)malloc(sizeof(int) * SIDE_SQUARE * SIDE_SQUARE)))
		error("Malloc error");
	ft_intset(color_field, PLAYER_2, SIDE_SQUARE * SIDE_SQUARE);
	return (color_field);
}

int	*get_player3(t_visualizer *vis)
{
	int	*color_field;

	if (SIDE_SQUARE == WARCRAFT_SQUARE)
		return (get_undead());
	if (!(color_field = (int *)malloc(sizeof(int) * SIDE_SQUARE * SIDE_SQUARE)))
		error("Malloc error");
	ft_intset(color_field, PLAYER_3, SIDE_SQUARE * SIDE_SQUARE);
	return (color_field);
}

int	*get_player4(t_visualizer *vis)
{
	int	*color_field;

	if (SIDE_SQUARE == WARCRAFT_SQUARE)
		return (get_elf());
	if (!(color_field = (int *)malloc(sizeof(int) * SIDE_SQUARE * SIDE_SQUARE)))
		error("Malloc error");
	ft_intset(color_field, PLAYER_4, SIDE_SQUARE * SIDE_SQUARE);
	return (color_field);
}
