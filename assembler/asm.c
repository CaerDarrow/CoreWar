/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:41:52 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/05/24 22:59:18 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"
#include <stdio.h>

int  main(int argc, char **argv)
{
	unit_t *unit;
	unsigned char	*ptr;
	int i;
	int fd;
	unsigned char buffer[CHAMP_MAX_SIZE];

	i = 0;
	// (void)(argc);
	// ptr = malloc(sizeof(unsigned char) * CHAMP_MAX_SIZE);
	// fd = open(argv[1], O_RDWR);
	// if (read(fd, buffer, CHAMP_MAX_SIZE))
	// {
	// 	ft_memcpy(ptr, buffer, CHAMP_MAX_SIZE);
	// }
	// while (i < CHAMP_MAX_SIZE)
	// {
	// 	printf("%02x", ptr[i]);
	// 	if ((i + 1) % 2 == 0)
	// 		printf(" ");
	// 	if ((i + 1) % 8 == 0)
	// 		printf("\n");
	// 	i++;
	// }
	unit = (unit_t *)malloc(sizeof(unit_t));
	ft_bzero(unit, CHAMP_MAX_SIZE);
	unit->add_name = &add_name;
	unit->add_comment = &add_comment;
	unit->header.magic = COREWAR_EXEC_MAGIC;
	unit->add_name("Batman", unit);
	unit->header.prog_size = COREWAR_EXEC_MAGIC;
	unit->add_comment("This city needs me", unit);
	ptr = (unsigned char *)unit;
	ft_memcpy(ptr, unit, CHAMP_MAX_SIZE);
	write(fd, ptr, CHAMP_MAX_SIZE);
	while (i < CHAMP_MAX_SIZE)
	{
		printf("%02x", ptr[i]);
		if ((i + 1) % 2 == 0)
			printf(" ");
		if ((i + 1) % 8 == 0)
			printf("\n");
		i++;
	}
	close(fd);
	//printf("%x", ptr);
	free(unit);
	return (0);
}
