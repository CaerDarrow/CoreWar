/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:41:52 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/05/28 16:30:11 by ajon-hol         ###   ########.fr       */
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


static void		read(char *filename)
{
	if (!(fd = open(filename, O_RDONLY)))
		//error
		;
	
}

int				main(int argc, char **argv)
{
	t_unit *unit;

	(void)(argc);
	unit = initchamp();
	writechamp(unit, argv[1]);
	//checkchamp("a.cor");
	free(unit);
	return (0);
}
