/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:01:26 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/05/28 20:59:31 by ajon-hol         ###   ########.fr       */
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

t_unit	*initchamp(void)
{
	t_unit *unit;

	unit = (t_unit *)malloc(sizeof(t_unit) + sizeof(char[22]));
	ft_bzero(unit, (sizeof(t_unit) + sizeof(char[22])));
	set_magic(unit);
	set_name("Batman", unit);
	set_prog_size(22, unit);
	set_comment("This city needs me", unit);
	set_exec((unsigned char *)"aaaaaaaaaaaaaaaaaaaaaa", unit->header.prog_size, unit);
	return (unit);
}

void	writechamp(t_unit *unit, char *fname)
{
	unsigned char	*ptr;
	char			*name;
	char			*newfile;
	size_t			i;
	int				fd;

	name = ft_strsub(fname, 0, (ft_strlen(fname) - 2));
	newfile = ft_strfjoin(&name, ".cor");
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
