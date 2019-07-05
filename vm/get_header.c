/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 15:55:37 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/04 18:24:30 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned int		get_magic(int fd, int cur_player)
{
	unsigned char	b[BYTE(4)];

	if (read(fd, &b, BYTE(4)) != BYTE(4))
		champ_error("Not binary file", cur_player);
	return ((b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3]);
}

void				get_prog_name(int fd, char s[], int cur_player)
{
	if (read(fd, s, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		champ_error("Invalid champion programm name", cur_player);
	s[PROG_NAME_LENGTH] = 0;
	if (!get_null(fd))
		champ_error("Null not found", cur_player);
}

unsigned int		get_prog_size(int fd, int cur_player)
{
	unsigned char	b[BYTE(4)];

	if (read(fd, &b, BYTE(4)) != BYTE(4))
		champ_error("Invalid champion programm size", cur_player);
	return ((b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3]);
}

void				get_comment(int fd, char s[], int cur_player)
{
	if (read(fd, s, COMMENT_LENGTH) != COMMENT_LENGTH)
		champ_error("Invalid champion comment", cur_player);
	s[COMMENT_LENGTH] = 0;
	if (!get_null(fd))
		champ_error("Null not found", cur_player);
}

unsigned char		*get_code(int fd, unsigned int size, int cur_player)
{
	unsigned char	*res;
	char			b;

	if (!(res = (unsigned char *)malloc(size + 1)))
		champ_error("Malloc error", cur_player);
	if (read(fd, res, size) != size)
		champ_error("Invalid champion programm code", cur_player);
	res[size] = 0;
	if (read(fd, &b, 1) != 0)
		champ_error("Invalid champion composition", cur_player);
	return (res);
}
