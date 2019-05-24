/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 21:49:16 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/05/24 22:22:25 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"

void add_name(char *name, unit_t *unit)
{
	ft_memcpy(unit->header.prog_name, name, ft_strlen(name));
}

void add_comment(char *comment, unit_t *unit)
{
	ft_memcpy(unit->header.comment, comment, ft_strlen(comment));
}
