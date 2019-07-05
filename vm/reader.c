/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:49:51 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/05 18:05:41 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int					get_null(int fd)
{
	char			b[BYTE(4)];

	if (read(fd, &b, BYTE(4)) != BYTE(4))
		return (0);
	if (b[0] != 0 || b[1] != 0 || b[2] != 0 || b[3] != 0)
		return (0);
	return (1);
}

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
	ft_memcpy(entity->bg + ((MEM_SIZE) * (cur_player - 1) / entity->n_players),
		code, champ->prog_size);
	ft_memdel((void **)&code);
	close(fd);
	return (champ);
}

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

static void			introduce(t_header *p, int n)
{
	ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", n,
		p->prog_size, p->prog_name, p->comment);
}

int					remove_n(t_list **l, int num)
{
	t_list			*t;

	t = *l;
	while (t)
	{
		if (*(int *)t->data == num)
		{
			if (!t->prev)
			{
				t = (*l)->next;
				if (t)
					t->prev = 0;
				ft_memdel((void **)&(*l)->data);
				ft_memdel((void **)l);
				*l = t;
			}
			else
			{
				t->prev->next = t->next;
				if (t->next)
					t->next->prev = t->prev;
				ft_memdel((void **)&t->data);
				ft_memdel((void **)&t);
			}
			return (1);
		}
		t = t->next;
	}
	return (0);
}

static int			get_next_free_number()
{
	int				b;

	if (!g_free_player_num)
		error("Invalid -n flag");
	if (g_n_flag <= 0)
	{
		b = *(int *)g_free_player_num->data;
		if (!remove_n(&g_free_player_num, b))
			error("Invalid -n flag");
		return (b);
	}
	b = g_n_flag;
	g_n_flag = -1;
	if (!remove_n(&g_free_player_num, b))
		error("Invalid -n flag");
	return (b);
}

void				read_champs(int argc, const char *argv[],
						t_game_entity *entity)
{
	int				i;
	int				n;
	t_header		*champ;

	if (!(entity->bg = (t_uchar *)malloc(MEM_SIZE)))
		error("Malloc error");
	ft_bzero(entity->bg, MEM_SIZE);
	entity->n_players = count_players(argc, argv);
	if (entity->n_players > MAX_PLAYERS || entity->n_players <= 0)
		error("Invalid quantity of champions (or invalid flags)");
	ft_printf("Introducing contestants...\n");
	i = 0;
	while (++i < argc)
		if (!(argv[i][0] == '-' && set_flags(argc, argv, entity, &i)))
		{
			champ = get_champ(argv[i], entity, (n = get_next_free_number()));
			g_n_flag = -1;
			ld_push_back(&entity->players, champ);
			introduce(champ, n);
		}
}
