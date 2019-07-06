/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_service.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:16:42 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/06 18:21:08 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			count_players(int argc, const char *argv[])
{
	int				res;
	int				i;

	i = 0;
	res = 0;
	while (++i < argc)
	{
		if (argv[i][0] != '-')
			res++;
		else if (ft_strcmp(argv[i], "-vis") == 0)
		{
			if (i + 1 < argc && ft_isnum((char *)argv[i + 1]))
				i++;
		}
		else if (ft_strcmp(argv[i], "-v") == 0 ||
			ft_strcmp(argv[i], "-d") == 0 ||
			ft_strcmp(argv[i], "-dump") == 0 ||
			ft_strcmp(argv[i], "-n") == 0)
			i++;
	}
	return (res);
}

void				introduce(t_header p, int n)
{
	ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", n,
		p.prog_size, p.prog_name, p.comment);
}

void				init_bg_and_players(int argc, const char *argv[],
						t_game_entity *entity)
{
	if (!(entity->bg = (t_uchar *)malloc(MEM_SIZE)))
		error("Malloc error");
	ft_bzero(entity->bg, MEM_SIZE);
	entity->n_players = count_players(argc, argv);
	if (entity->n_players > MAX_PLAYERS || entity->n_players <= 0)
		error("Invalid quantity of champions (or invalid flags)");
	ft_printf("Introducing contestants...\n");
}
