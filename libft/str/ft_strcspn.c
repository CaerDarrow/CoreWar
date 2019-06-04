/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 12:52:17 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/04 12:55:38 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *s1, const char *s2)
{

	size_t ret;

	ret = 0;
	while(*s1)
	{
		if (ft_strchr(s2, *s1))
			return ret;
		else
		{
			s1++;
			ret++;
		}
	}
	return ret;
}
