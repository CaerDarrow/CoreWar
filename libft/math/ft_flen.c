/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:12:43 by jjacobso          #+#    #+#             */
/*   Updated: 2019/01/26 17:13:09 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_flen(long double f)
{
	int					res;

	res = 0;
	while (f >= 1)
	{
		res++;
		f /= 10;
	}
	return (res);
}