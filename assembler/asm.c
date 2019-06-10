/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:41:52 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/10 20:56:52 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	main(int argc, char **argv)
{
	t_unit	*unit;
	t_list	*parsed;
	char	*readed;

	if (argc < 2)
		ft_printf("Usage: ./asm [possible flags] <sourcefile.s>\n");
	else if ((readed = read_s(argv[argc - 1])))
	{
		if ((parsed = parse(readed)))
		{
			unit = initchamp(/*readed*/);
			writechamp(unit, argv[argc - 1]);
			free(unit);
		}
		free(readed);
	}
	return (0);
}
