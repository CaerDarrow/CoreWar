/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:34:43 by jjacobso          #+#    #+#             */
/*   Updated: 2019/07/06 16:52:00 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			error(char *s)
{
	PRINT(RED"%s\n"RESET, s);
	exit(-1);
}

void			champ_error(char *s, int player)
{
	PRINT(RED"Champion %d"RESET" :: %s\n", player, s);
	exit(-1);
}
