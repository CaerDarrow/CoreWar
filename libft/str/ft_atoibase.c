/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoibase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:38:34 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/23 17:56:45 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				to_int(char c, int mbase)
{
	if (ft_isalpha(c))
		return (mbase - ('f' - c));
	return (c - '0');
}

int				ft_atoibase(char *s, int mbase)
{
	int			res;

	s = ft_strlower(s);
	res = 0;
	while (s && *s)
	{
		res = res * mbase + to_int(*s, (mbase - 1));
		s++;
	}
	return (res);
}
