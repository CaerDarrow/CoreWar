/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:29:46 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/05/28 22:18:34 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_name(char *fname)
{
	size_t	len;
	char	*ext;

	len = ft_strlen(fname);
	if ((len >= 2) && (ext = ft_strrchr(fname, '.')) && (ft_strequ(ext, ".s")))
		return (1);
	return (0);
}

int			read_s(char *fname)
{
	int	fd;

	if (check_name(fname))
	{
		if ((fd = open(fname, O_RDONLY)) != -1)
		{
			close(fd);
			return (1);
		}
	}
	ft_printf("Can't read source file %s\n", fname);
	return (0);
}
