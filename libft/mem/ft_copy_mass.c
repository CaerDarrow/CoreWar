/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_mass.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:42:15 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/05 19:38:35 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				**ft_copy_mass(void **mas, int size)
{
	char			**s;
	char			**res;
	int				i;

	if (!(res = malloc(size * sizeof(void *))))
		return (NULL);
	s = (char **)mas;
	i = -1;
	while (++i < size)
	{
		res[i] = ft_strdup(s[i]);
	}
	return ((void**)res);
}
