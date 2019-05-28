/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:01:26 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/05/28 16:04:01 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_unit	*initchamp(void)
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

void	writechamp(t_unit *unit, char *filename)
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
		// ft_printf("%02x", ptr[i]);
		// if ((i + 1) % 2 == 0)
		// 	ft_printf(" ");
		// if ((i + 1) % 16 == 0)
		// 	ft_printf("\n");
		i++;
	}
	//ft_printf("\n______________\n");
	close(fd);
}
