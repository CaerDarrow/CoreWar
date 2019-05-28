/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:34:43 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/28 15:32:26 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			error(char *s)
{
	ft_printf(RED"%s\n"RESET, s);
	exit(-1);
}

void			champ_error(char *s, int player)
{
	ft_printf(RED"Champion %d"RESET" :: %s\n", player, s);
	exit(-1);
}
