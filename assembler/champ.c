/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:01:26 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/03 18:59:02 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static size_t	writerev(size_t start, int fd, unsigned char *ptr)
{
	int i;

	i = 3;
	while (i >= 0)
	{
		write(fd, &(ptr[i + start]), sizeof(ptr[i + start]));
		i--;
	}
	return (start + 4);
}

void			writechamp(t_unit *unit, char *fname)
{
	unsigned char	*ptr;
	char			*name;
	char			*newfile;
	size_t			i;
	int				fd;

	name = ft_strsub(fname, 0, (ft_strlen(fname) - 2)); //malloc
	newfile = ft_strfjoin(&name, ".cor"); // malloc
	fd = open(newfile, O_RDWR | O_CREAT | O_TRUNC, 0755);
	ptr = (unsigned char *)unit;
	i = 0;
	while (i < (sizeof(t_unit) + unit->header.prog_size))
	{
		if (i == 0 || i == 136)
			i = writerev(i, fd, ptr);
		else
		{
			write(fd, &(ptr[i]), sizeof(ptr[i]));
			i++;
		}
	}
	ft_printf("Writing output program to %s\n", newfile);
	free(newfile);
	close(fd);
}
