/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:49:51 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/24 22:03:51 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			valide_champ(const char *s)
{
	(void)s;
	return (1);
}

static void			get_champ(const char *s, t_game_entity *entity,
						int cur_player)
{
	t_header		*champ;
	char			*code;
	int				i;
	int				fd;
	if ((fd = open(s, O_RDONLY)) < 0)
		error("Cant open file");
	// ft_printf("%d",COREWAR_EXEC_MAGIC);
	if (!(champ = (t_header *)malloc(sizeof(t_header))))
		error("Malloc error");
	if ((champ->magic = get_magic()) != COREWAR_EXEC_MAGIC)
		error("Invalid champion");
	champ->prog_name = get_prog_name();
	champ->prog_size = get_prog_size();
	champ->comment = get_comment();
	code = get_code();
	ft_strncpy(entity->bg + (MEM_SIZE * cur_player / entity->players),
		code, ft_strlen(code));// len - 1 ?
	// (void)i;
	// i = 0;
	// char b =0;
	// while (read(fd, &b, 1) == 1)
	// {
	// 	entity->bg[i++ + MEM_SIZE * cur_player / entity->players] = b;
	// }
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
