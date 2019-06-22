/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_warcraft.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 18:53:24 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 18:53:27 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char	g_mini_pictures_pathes[4][200] =
{
	"/Users/gleonett/Desktop/CW/vm/vis/mini_orc",
	"/Users/gleonett/Desktop/CW/vm/vis/mini_human",
	"/Users/gleonett/Desktop/CW/vm/vis/mini_undead",
	"/Users/gleonett/Desktop/CW/vm/vis/mini_elf"
};

static int	*read_mini_picture(int player)
{
	const int	fd = open(g_mini_pictures_pathes[player - 1], O_RDONLY);
	char		line[3000];
	int			*picture;
	int			i;
	int			j;

	if (!(picture = (int *)malloc(sizeof(int) * 324)))
		error("Malloc error");
	ft_bzero(line, sizeof(char) * 3000);
	read(fd, line, 30000);
	close(fd);
	i = -1;
	j = 0;
	while (j < 324)
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
