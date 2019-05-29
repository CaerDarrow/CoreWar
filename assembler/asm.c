/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:41:52 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/05/29 14:36:51 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	main(int argc, char **argv)
{
	t_unit *unit;

	if (argc < 2)
		ft_printf("Usage: ./asm [possible flags] <sourcefile.s>\n");
	else if (read_s(argv[argc - 1]))
	{
		unit = initchamp();
		writechamp(unit, argv[argc - 1]);
		free(unit);
	}
	return (0);
}
