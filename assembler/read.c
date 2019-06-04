/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:29:46 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/04 15:04:47 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// static char	**ft_readlines(int fd)
// {
// 	char *line;
// 	char **rd;
// 	size_t i;
//
// 	if (!(rd = (char **)malloc(sizeof(*rd))))
// 		exit(1);
// 	i = 0;
// 	while (get_next_line(fd, &line))
// 	{
// 		if (i > 0 && !(rd = (char **)realloc(rd, sizeof(*rd) * (i + 1))))
// 			exit(1);
// 		rd[i] = ft_strdup(line);
// 		ft_memdel((void **)&line);
// 		if (!(rd[i]))
// 		{
// 			ft_freemas(&rd, 0);
// 			exit(1);
// 		}
// 		i++;
// 	}
// 	if (!(rd = (char **)realloc(rd, sizeof(*rd) * i)))
// 	{
// 		ft_freemas(&rd, 0);
// 		exit(1);
// 	}
// 	rd[i] = NULL;
// 	return(rd);
// }

static int		check_fname(char *fname)
{
	size_t	len;
	char	*ext;

	len = ft_strlen(fname);
	if ((len >= 2) && (ext = ft_strrchr(fname, '.')) && (ft_strequ(ext, ".s")))
		return (1);
	return (0);
}
static size_t	ft_getfsize(char *fname)
{
	int		fd;
	size_t	size;

	size = 0;
	if ((fd = open(fname, O_RDONLY)) != -1)
	{
		size = lseek(fd, (size_t)0, SEEK_END);
		close(fd);
	}
	return (size);
}

static char		*ft_read(char *fname, const size_t fsize)
{
	char		*buf;
	int			fd;

	if (!(buf = (char *)malloc(sizeof(char) * (fsize + 1))))
		return (NULL);
	if ((fd = open(fname, O_RDONLY)) != -1)
	{
		if (read(fd, buf, (fsize + 1)))
		{
			buf[fsize] = '\0';
			close(fd);
			return(buf);
		}
		close(fd);
	}
	return(NULL);
}

int				read_s(char *fname)
{
	char *rd;

	if (check_fname(fname))
	{
		if ((rd = ft_read(fname, ft_getfsize(fname))))
		{
			parse(rd);
			free(rd);
			return (1);
		}
	}
	ft_printf("Can't read source file %s\n", fname);
	return (0);
}
