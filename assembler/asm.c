/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:41:52 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/07 20:42:48 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	main(int argc, char **argv)
{
	t_unit	*unit;
	char	*rd;

	if (argc < 2)
		ft_printf("Usage: ./asm [possible flags] <sourcefile.s>\n");
	else if ((rd = read_s(argv[argc - 1])))
	{
		if (parse(rd))
		{
			unit = initchamp(/*readed*/);
			writechamp(unit, argv[argc - 1]);
			free(unit);
		}
		free(rd);
	}
	return (0);
}
