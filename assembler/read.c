/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:29:46 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/07 20:42:22 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
			return (buf);
		}
		close(fd);
	}
	return (NULL);
}

char			*read_s(char *fname)
{
	char	*rd;

	if (check_fname(fname) && (rd = ft_read(fname, ft_getfsize(fname))))
		return (rd);
	ft_printf("Can't read source file %s\n", fname);
	return (NULL);
}
