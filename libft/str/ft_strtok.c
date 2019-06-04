/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 12:46:51 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/04 17:55:40 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *s, const char *delim)
{
	static char	*lasts;
	int			ch;

	if (s == 0)
		s = lasts;
	if ((ch = *s++) == '\0')
		return 0;
	while (ft_strchr(delim, ch))
	{
		if ((ch = *s++) == '\0')
			return 0;
	}
	--s;
	lasts = s + ft_strcspn(s, delim);
	if (*lasts != 0)
		*lasts++ = 0;
	return s;
}
