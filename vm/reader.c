/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:49:51 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/28 16:22:33 by ajon-hol         ###   ########.fr       */
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
	t_unit			*champ;
	int				fd;

	if ((fd = open(s, O_RDONLY)) < 0)
		error("Cant open file");
	if (!(champ = (t_unit *)malloc(sizeof(t_unit))))
		error("Malloc error");
	if ((champ->header.magic = get_magic(fd)) != COREWAR_EXEC_MAGIC)
		error("Invalid champion1");
	get_prog_name(fd, champ->header.prog_name);
	if ((champ->header.prog_size = get_prog_size(fd)) > CHAMP_MAX_SIZE)
		error("Invalid champion");
	get_comment(fd, champ->header.comment);
	champ->exec = get_code(fd, champ->header.prog_size);
	ft_memcpy(entity->bg + (MEM_SIZE * cur_player / entity->players),
		champ->exec, champ->header.prog_size);
	ft_memdel((void **)&champ->exec);
	ld_push_back(&entity->player, champ);
	// ft_printf("%u %s %u %s\n", champ->magic, champ->prog_name, champ->prog_size, champ->comment);
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
	entity->players = argc - 1;
	i = 0;
	while (++i < argc)
		get_champ(argv[i], entity, i - 1);
}
// 0b 68 01 00 07 00 01 01 00 00 00 00 02 90 00 00 00 00 02 09 ff ed 00
