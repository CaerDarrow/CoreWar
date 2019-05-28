/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:49:51 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/28 20:01:01 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// static int			valide_champ(const char *s)
// {
// 	(void)s;
// 	return (1);
// }

static void			get_champ(const char *s, t_game_entity *entity,
						int cur_player)
{
	t_header		*champ;
	unsigned char	*code;
	int				fd;

	if ((fd = open(s, O_RDONLY)) < 0)
		champ_error("Cant open file", cur_player);
	if (!(champ = (t_header *)malloc(sizeof(t_header))))
		champ_error("Malloc error", cur_player);
	if ((champ->magic = get_magic(fd, cur_player)) != COREWAR_EXEC_MAGIC)
		champ_error("Invalid champion magic header", cur_player);
	get_prog_name(fd, champ->prog_name, cur_player);
	if ((champ->prog_size = get_prog_size(fd, cur_player)) > CHAMP_MAX_SIZE)
		champ_error("Invalid champion programm size", cur_player);
	get_comment(fd, champ->comment, cur_player);
	code = get_code(fd, champ->prog_size, cur_player);
	ft_memcpy(entity->bg + (MEM_SIZE * cur_player / entity->n_players),
		code, champ->prog_size);
	ft_memdel((void **)&code);
	ld_push_back(&entity->players, champ);
	close(fd);
}

void				read_champs(int argc, const char *argv[],
						t_game_entity *entity)
{
	int				i;

	if (!(entity->bg = (unsigned char *)malloc(MEM_SIZE)))
		error("Malloc error");
	ft_bzero(entity->bg, MEM_SIZE);
	if (argc - 1 > MAX_PLAYERS)
		error("Too many players");
	entity->n_players = argc - 1;
	i = 0;
	while (++i < argc)
		get_champ(argv[i], entity, i - 1);
}
