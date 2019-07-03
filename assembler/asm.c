/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:41:52 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/07/03 16:27:56 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	lcondel(t_list **parsed)
{
	t_token		*token;

	if (parsed && *parsed && (token = (t_token *)((*parsed)->data)))
	{
		ft_memdel((void **)&token->token);
		ft_memdel((void **)&(*parsed)->data);
	}
}

int			main(int argc, char **argv)
{
	t_unit	*unit;
	t_list	*parsed;
	char	*readed;
	int		psize;

	psize = 0;
	if (argc < 2)
		ft_printf("Usage: ./asm [possible flags] <sourcefile.s>\n");
	else if ((readed = read_s(argv[argc - 1])))
	{
		if ((parsed = parse(readed)))
		{
			if ((psize = syntax(&parsed)))
			{
				translate_labels(&parsed);
				unit = encode(&parsed, psize);
				writechamp(unit, argv[argc - 1]);
				free(unit);
			}
			//l_iter(&parsed, printtoken);
			l_delall(&parsed, lcondel);
		}
		free(readed);
	}
	return (0);
}
