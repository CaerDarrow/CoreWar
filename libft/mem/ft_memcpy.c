/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 20:10:45 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/27 17:42:13 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memcpy(void *dest, const void *src, size_t len)
{
	char		*d;
	const char	*s;

//	ft_printf("dest = %p\n src = %p, len = %zu\n", dest, src, len);
	d = dest;
	s = src;
	while (len--)
		*d++ = *s++;
//	ft_printf("kek\n");
	return (dest);
}
