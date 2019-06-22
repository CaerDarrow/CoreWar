/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_final_picture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 16:10:44 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 16:16:56 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char	g_pictures_pathes[4][200] =
{
	"/Users/gleonett/Desktop/CW/vm/vis/orc",
	"/Users/gleonett/Desktop/CW/vm/vis/human",
	"/Users/gleonett/Desktop/CW/vm/vis/undead",
	"/Users/gleonett/Desktop/CW/vm/vis/elf"
};

int			*get_final_picture(int player)
{
	const int	fd = open(g_pictures_pathes[player - 1], O_RDONLY);
	char		*line;
	int			*picture;
	int			i;
	int			j;

	if (!(picture = (int *)malloc(sizeof(int) * 1653796)))
		error("Malloc error");
	get_next_line(fd, &line);
	close(fd);
	i = -1;
	j = 0;
	while (j < SIDE_PICTURE * SIDE_PICTURE)
	{
		picture[j++] = ft_atoi(line + i + 1);
		while (line[++i] != '\0' && line[i] != ',')
			;
	}
	ft_memdel((void **)&line);
	return (picture);
}
