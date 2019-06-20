/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajon-hol <ajon-hol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:14:54 by ajon-hol          #+#    #+#             */
/*   Updated: 2019/06/20 18:43:10 by ajon-hol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	f_error(t_list **lst)
{
	//Champion name too long (Max length 128)
	//Champion coment too long (Max length 2048)
	ft_printf("Syntax error at token: ");
	printtoken(lst);
	exit(1);
}
