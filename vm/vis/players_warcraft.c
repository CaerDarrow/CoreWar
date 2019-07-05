/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_warcraft.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 18:53:24 by gleonett          #+#    #+#             */
/*   Updated: 2019/07/05 15:58:43 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char	g_mini_pictures_pathes[4][200] =
{
	"vm/vis/textures/mini_orc",
	"vm/vis/textures/mini_human",
	"vm/vis/textures/mini_undead",
	"vm/vis/textures/mini_elf"
};

static int	*read_mini_picture(int player)
{
	const int	fd = open(g_mini_pictures_pathes[player - 1], O_RDONLY);
	char		line[NUM_SMBLS_MINI];
	int			*picture;
	int			i;
	int			j;

	if (!(picture = (int *)malloc(sizeof(int) * 324)))
		error("Malloc error");
	ft_bzero(line, sizeof(char) * NUM_SMBLS_MINI);
	read(fd, line, NUM_SMBLS_MINI);
	close(fd);
	i = -1;
	j = 0;
	while (j < WARCRAFT_SQUARE * WARCRAFT_SQUARE)
	{
		picture[j++] = ft_atoi(line + i + 1);
		while (line[++i] != '\0' && line[i] != ',')
			;
	}
	return (picture);
}

int			*get_horde(void)
{
	return (read_mini_picture(1));
}

int			*get_alliance(void)
{
	return (read_mini_picture(2));
}

int			*get_undead(void)
{
	return (read_mini_picture(3));
}

int			*get_elf(void)
{
	return (read_mini_picture(4));
}
