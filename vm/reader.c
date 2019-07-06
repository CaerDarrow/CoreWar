/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:49:51 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/06 20:12:10 by jjacobso         ###   ########.fr       */
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

static t_header		get_champ(const char *s, t_game_entity *entity,
						int cur_player)
{
	t_header		champ;
	t_uchar			code[CHAMP_MAX_SIZE + 1];
	int				fd;

	if ((fd = open(s, O_RDONLY)) < 0)
		champ_error("Cant open file", cur_player);
	if ((champ.magic = get_magic(fd, cur_player)) != COREWAR_EXEC_MAGIC)
		champ_error("Not binary file", cur_player);
	get_prog_name(fd, champ.prog_name, cur_player);
	if ((champ.prog_size = get_prog_size(fd, cur_player)) > CHAMP_MAX_SIZE)
		champ_error("Invalid champion programm size", cur_player);
	get_comment(fd, champ.comment, cur_player);
	get_code(fd, code, champ.prog_size, cur_player);
	ft_memcpy(entity->bg + ((MEM_SIZE) * (cur_player - 1) / entity->n_players),
		code, champ.prog_size);
	close(fd);
	return (champ);
}

static int			get_player_num(int n)
{
	if (g_n_flag > 0)
	{
		n = g_n_flag;
		g_n_flag = -1;
	}
	else
	{
		if (g_taken_player_num & (1 << (n - 1)))
		{
			n = 1;
			while (g_taken_player_num & (1 << (n - 1)))
				n++;
		}
		if (n > 4)
			error("invalid -n flag");
	}
	return (n);
}

void				read_champs(int argc, const char *argv[],
						t_game_entity *entity)
{
	int				i;
	int				n;
	int				num;
	t_header		players_sequence[MAX_PLAYERS];

	init_bg_and_players(argc, argv, entity);
	i = 0;
	n = 1;
	while (++i < argc)
		if (!(argv[i][0] == '-' && set_flags(argc, argv, entity, &i)))
		{
			num = get_player_num(n++);
			g_taken_player_num += 1 << (num - 1);
			players_sequence[num - 1] = get_champ(argv[i], entity, num);
		}
	i = 0;
	while (++i <= entity->n_players)
	{
		entity->players[i - 1] = players_sequence[i - 1];
		introduce(entity->players[i - 1], i);
	}
}
