/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 18:10:51 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/05 19:14:55 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			set_vis_flag(int argc, const char *argv[],
						t_game_entity *entity, int *i)
{
	++*i;
	if (*i >= argc)
		error("Invalid flag (-vis)");
	if (!ft_isnum((char *)argv[*i]))
	{
		entity->vis_key = 10;
		--*i;
		return ;
	}
	if (*i + 1 < argc)
	{
		entity->vis_key = ft_atoi(argv[*i]);
	}
	else
	{
		entity->vis_key = 10;
		--*i;
	}
	if (!ft_inrange(entity->vis_key, 1, 18))
		error("Invalid size (-vis)");
}

static int			set_flags_part_2(int argc, const char *argv[],
						t_game_entity *entity, int *i)
{
	if (ft_strcmp(argv[*i], "-d") == 0)
	{
		if (++*i >= argc || !ft_isnum((char *)argv[*i]))
			error("Invalid flag (-d)");
		g_d_flag = ft_atoi(argv[*i]);
		if (g_d_flag < 0)
			error("Invalid flag (-d)");
		return (1);
	}
	else if (ft_strcmp(argv[*i], "-a") == 0)
		return ((entity->print_aff = 1));
	if (ft_strcmp(argv[*i], "-n") == 0)
	{
		if (++*i >= argc || !ft_isnum((char *)argv[*i]))
			error("Invalid flag (-n)");
		g_n_flag = ft_atoi(argv[*i]);
		if (!ft_inrange(g_n_flag, 1, entity->n_players) ||
			!l_int_find(g_free_player_num, g_n_flag))
			error("Invalid flag (-n)");
		return (1);
	}
	else
		error("Wrong flag");
	return (0);
}

int					set_flags(int argc, const char *argv[],
						t_game_entity *entity, int *i)
{
	if (ft_strcmp(argv[*i], "-vis") == 0)
	{
		set_vis_flag(argc, argv, entity, i);
		return (1);
	}
	else if (ft_strcmp(argv[*i], "-v") == 0)
	{
		++*i;
		if (*i >= argc || !ft_isnum((char *)argv[*i]))
			error("Invalid flag (-v)");
		g_verbose = ft_atoi(argv[*i]);
		return (1);
	}
	else if (ft_strcmp(argv[*i], "-dump") == 0)
	{
		++*i;
		if (*i >= argc || !ft_isnum((char *)argv[*i]))
			error("Invalid flag (-dump)");
		g_dump_flag = ft_atoi(argv[*i]);
		if (g_dump_flag < 0)
			error("Invalid flag (-dump)");
		return (1);
	}
	return (set_flags_part_2(argc, argv, entity, i));
}
