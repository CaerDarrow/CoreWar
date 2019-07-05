/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_picture_warcraft.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 16:10:44 by gleonett          #+#    #+#             */
/*   Updated: 2019/07/05 15:58:37 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char	g_pictures_pathes[4][200] =
{
	"vm/vis/textures/orc",
	"vm/vis/textures/human",
	"vm/vis/textures/undead",
	"vm/vis/textures/elf"
};

int			*get_final_picture(int winner)
{
	const int	fd = open(g_pictures_pathes[winner - 1], O_RDONLY);
	char		*line;
	int			*picture;
	int			i;
	int			j;

	if (!(picture = (int *)malloc(sizeof(int) * (SIDE_PICTURE * SIDE_PICTURE))))
		error("Malloc error");
	if (!(line = ft_strnew(NUM_SMBLS_PICTURE)))
		error("Malloc error");
	read(fd, line, NUM_SMBLS_PICTURE);
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
