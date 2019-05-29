/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:29:46 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/05/29 20:49:28 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_fname(char *fname)
{
	size_t	len;
	char	*ext;

	len = ft_strlen(fname);
	if ((len >= 2) && (ext = ft_strrchr(fname, '.')) && (ft_strequ(ext, ".s")))
		return (1);
	return (0);
}

static char	**ft_readlines(int fd)
{
	char *line;
	char **readed;
	size_t i;

	readed = (char **)malloc(sizeof(*readed));
	i = 0;
	while (get_next_line(fd, &line))
	{
		if (i > 0)
			readed = (char **)realloc(readed, sizeof(*readed) * (i + 1));
		readed[i] = ft_strdup(line);
		ft_memdel((void **)&line);
		i++;
	}
	readed = (char **)realloc(readed, sizeof(*readed) * (i + 1));
	readed[i] = NULL;
	return(readed);
}

int			read_s(char *fname)
{
	int	fd;
	char **readed;

	if (check_fname(fname))
	{
		if ((fd = open(fname, O_RDONLY)) != -1)
		{
			readed = ft_readlines(fd);
			parse(readed);
			ft_freemas(&readed, 0);
			close(fd);
			return (1);
		}
	}
	ft_printf("Can't read source file %s\n", fname);
	return (0);
}
