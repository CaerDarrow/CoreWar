/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:41:52 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/05/27 20:47:16 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		checkchamp(char *filename)
{
	int				i;
	int				k;
	int				fd;
	unsigned char	buffer[sizeof(t_unit)];

	fd = open(filename, O_RDWR, 0755);
	if (read(fd, buffer, sizeof(t_unit)))
	{
		i = 0;
		while (i < CHAMP_MAX_SIZE)
		{
			printf("%02x", buffer[i]);
			if ((i + 1) % 2 == 0)
				printf(" ");
			if ((i + 1) % 16 == 0)
				printf("\n");
			i++;
		}
	}
	k = 0;
	k = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
	printf("\n%#x\n", k);
	close(fd);
}

static t_unit	*initchamp(void)
{
	t_unit *unit;

	unit = (t_unit *)malloc(sizeof(t_unit));
	ft_bzero(unit, CHAMP_MAX_SIZE);
	set_magic(unit);
	set_name("Batman", unit);
	set_prog_size((void *)22, unit);
	set_comment("This city needs me", unit);
	return (unit);
}

static void		writechamp(t_unit *unit, char *filename)
{
	unsigned char	*ptr;
	size_t			i;
	int				fd;

	fd = open(ft_strjoin(filename, ".cor"), O_RDWR | O_CREAT, 0755);
	ptr = (unsigned char *)unit;
	i = 0;
	while (i < sizeof(t_unit))
	{
		write(fd, &(ptr[i]), sizeof(ptr[i]));
		printf("%02x", ptr[i]);
		if ((i + 1) % 2 == 0)
			printf(" ");
		if ((i + 1) % 16 == 0)
			printf("\n");
		i++;
	}
	printf("\n______________\n");
	close(fd);
}

int				main(int argc, char **argv)
{
	t_unit *unit;

	(void)(argc);
	unit = initchamp();
	writechamp(unit, argv[1]);
	checkchamp("a.cor");
	free(unit);
	return (0);
}
