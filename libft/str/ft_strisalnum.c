/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisalnum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:35:00 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/05 18:36:37 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strisalnum(char *str)
{
	while (*str)
	{
		if (!(ft_isalpha(*str) || ft_isdigit(*str)))
			return (0);
		str++;
	}
	return (1);
}
