/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:29:46 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/05/29 14:59:26 by ajon-hol         ###   ########.fr       */
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

static char	**ft_readlines(int fd)
{
	char *line;
	char **parsed;
	size_t i;

	parsed = (char **)malloc(sizeof(*parsed));
	i = 0;
	while (get_next_line(fd, &line))
	{
		if (i > 0)
			parsed = (char **)realloc(parsed, sizeof(*parsed) * (i + 1));
		parsed[i] = ft_strdup(line);
		ft_memdel((void **)&line);
		i++;
	}
	parsed = (char **)realloc(parsed, sizeof(*parsed) * (i + 1));
	parsed[i] = NULL;
	return(parsed);
}

int			read_s(char *fname)
{
	int	fd;
	char **parsed;

	if (check_name(fname))
	{
		if ((fd = open(fname, O_RDONLY)) != -1)
		{
			parsed = ft_readlines(fd);
			while (*parsed)
			{
				ft_printf("%s\n", *parsed);
				parsed++;
			}
			close(fd);
			return (1);
		}
	}
	ft_printf("Can't read source file %s\n", fname);
	return (0);
}
