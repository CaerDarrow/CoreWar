/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 15:55:37 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/27 20:18:00 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				get_null(int fd)
{
	char			b[BYTE(4)];

	if (read(fd, &b, BYTE(4)) != BYTE(4))
		return (0);
	if (b[0] != 0 || b[1] != 0 || b[2] != 0 || b[3] != 0)
		return (0);
	return (1);
}

unsigned int		get_magic(int fd)
{
	unsigned char	b[BYTE(4)];

	if (read(fd, &b, BYTE(4)) != BYTE(4))
		error("Not valid champion");
	return ((b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3]);
}

void				get_prog_name(int fd, char s[])
{
	if (read(fd, s, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		error("Not valid champion");
	s[PROG_NAME_LENGTH] = 0;
	if (!get_null(fd))
		error("Not valid champion");
}

unsigned int		get_prog_size(int fd)
{
	unsigned char	b[BYTE(4)];

	if (read(fd, &b, BYTE(4)) != BYTE(4))
		error("Not valid champion3");
	return ((b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3]);
}

void				get_comment(int fd, char s[])
{
	if (read(fd, s, COMMENT_LENGTH) != COMMENT_LENGTH)
		error("Not valid champion1");
	s[COMMENT_LENGTH] = 0;
	if (!get_null(fd))
		error("Not valid champion2");
}

unsigned char		*get_code(int fd, unsigned int size)
{
	unsigned char	*res;
	char			b;

	if (!(res = (unsigned char *)malloc(size + 1)))
		error("Malloc error");
	if (read(fd, res, size) != size)
		error("Not valid champion22");
	res[size] = 0;
	if (read(fd, &b, 1) != 0)
		error("Not valid champion33");
	return (res);
}
