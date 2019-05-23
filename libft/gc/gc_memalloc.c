/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:34:50 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/23 18:34:53 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	*gc_memalloc(size_t size, char *section)
{
	void *obl;

	obl = malloc(size);
	if (obl == NULL)
		return (NULL);
	ft_bzero(obl, size);
	gc(obl, section, GC_ADD);
	return (obl);
}
