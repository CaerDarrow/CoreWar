/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 18:10:51 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/04 18:11:16 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			set_flags_part_2(int argc, const char *argv[],
						t_game_entity *entity, int *i)
{
	if (ft_strcmp(argv[*i], "-d") == 0)
	{
		++*i;
		if (*i >= argc)
			error("Invalid flag (-d)");
		g_d_flag = atoi(argv[*i]);
		if (g_d_flag < 0)
			error("Invalid flag (-d)");
		return (1);
	}
	else if (ft_strcmp(argv[*i], "-a") == 0)
	{
		entity->print_aff = 1;
		return (1);
	}
	else
		error("Wrong flag");
	return (0);
}

int					set_flags(int argc, const char *argv[],
						t_game_entity *entity, int *i)
{
	if (ft_strcmp(argv[*i], "-v") == 0)
	{
		++*i;
		if (*i >= argc)
			error("Invalid flag (-v)");
		g_verbose = atoi(argv[*i]);
		return (1);
	}
	else if (ft_strcmp(argv[*i], "-dump") == 0)
	{
		++*i;
		if (*i >= argc)
			error("Invalid flag (-dump)");
		g_dump_flag = atoi(argv[*i]);
		if (g_dump_flag < 0)
			error("Invalid flag (-dump)");
		return (1);
	}
	return (set_flags_part_2(argc, argv, entity, i));
}
