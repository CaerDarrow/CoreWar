/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:15:12 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/23 18:34:27 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	*gc_malloc(size_t size, char *section)
{
	void *obl;

	obl = malloc(size);
	if (obl == NULL)
		return (NULL);
	gc(obl, section, GC_ADD);
	return (obl);
}
