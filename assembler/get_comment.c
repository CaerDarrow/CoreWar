/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:14:44 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/10 19:34:59 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_comment(char *rd, int *i)
{
	char	*test;
	int		j;

	j = *I;
	while (!(rd[*I] == '\n' || rd[*I] == '\0'))
		(*i)++;
	test = ft_strsub(rd, j, (*I - j));
	ft_printf("[COMMENT {%s}]", test);
}
