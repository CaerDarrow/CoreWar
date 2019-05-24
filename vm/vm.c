/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjacobso <jjacobso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:24:45 by jjacobso          #+#    #+#             */
/*   Updated: 2019/05/24 15:26:39 by jjacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void		set_flags(int argc, const char *argv[])
{
	(void)argc;
	(void)argv;
}

int				main(int argc, char const *argv[])
{
	if (argc != 1)
		set_flags(argc, argv);
	return (0);
}
