/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:49:51 by jjacobso          #+#    #+#             */
/*   Updated: 2019/06/10 12:54:27 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_header		*get_champ(const char *s, t_game_entity *entity,
						int cur_player)
{
	t_header		*champ;
	t_uchar			*code;
	int				fd;

	if ((fd = open(s, O_RDONLY)) < 0)
		champ_error("Cant open file", cur_player);
	if (!(champ = (t_header *)malloc(sizeof(t_header))))
		champ_error("Malloc error", cur_player);
	if ((champ->magic = get_magic(fd, cur_player)) != COREWAR_EXEC_MAGIC)
		champ_error("Not binary file", cur_player);
	get_prog_name(fd, champ->prog_name, cur_player);
	if ((champ->prog_size = get_prog_size(fd, cur_player)) > CHAMP_MAX_SIZE)
		champ_error("Invalid champion programm size", cur_player);
	get_comment(fd, champ->comment, cur_player);
	code = get_code(fd, champ->prog_size, cur_player);
	ft_memcpy(entity->bg + (MEM_SIZE * (cur_player - 1) / entity->n_players),
		code, champ->prog_size);
	ft_memdel((void **)&code);
	close(fd);
	return (champ);
}

static void			introduce(t_header *p, int n)
{
	ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", n,
		p->prog_size, p->prog_name, p->comment);
}

static void			set_flags(int argc, const char *argv[],
						t_game_entity *entity, int *i)
{
	(void)entity;
	if (ft_strcmp(argv[*i], "-v") == 0)
	{
		++*i;
		if (*i >= argc)
			error("Invalid flag");
		g_verbose = VERBOSE_LVL(atoi(argv[*i]));
	}
	else
		error("Invalid flag");
}

static int			count_players(int argc, const char *argv[])
{
	int				res;

	res = 0;
	while (--argc > 0)
	{
		if (argv[argc][0] != '-')
			res++;
		else if (ft_strcmp(argv[argc], "-v") == 0)
			res--;
	}
	return (res);
}

void				read_champs(int argc, const char *argv[],
						t_game_entity *entity)
{
	int				i;
	t_header		*champ;
	int				n;

	if (!(entity->bg = (t_uchar *)malloc(MEM_SIZE)))
		error("Malloc error");
	ft_bzero(entity->bg, MEM_SIZE);
	if (argc - 1 > MAX_PLAYERS)
		error("Too many players");
	entity->n_players = count_players(argc, argv);
	ft_printf("Introducing contestants...\n");
	i = 0;
	n = 1;
	while (++i < argc)
		if (argv[i][0] == '-')
			set_flags(argc, argv, entity, &i);
		else
		{
			champ = get_champ(argv[i], entity, n);
			ld_push_back(&entity->players, champ);
			introduce(champ, n);
			n++;
		}
}
