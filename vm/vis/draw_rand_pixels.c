/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rand_pixels.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 17:25:37 by gleonett          #+#    #+#             */
/*   Updated: 2019/06/22 17:25:39 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	shuffle(int *arr, int n)
{
	int	i;
	int	j;
	int	tmp;

	srand(time(NULL));
	i = n;
	while (--i > -1)
	{
		j = rand() % (i + 1);
		tmp = arr[j];
		arr[j] = arr[i];
		arr[i] = tmp;
	}
}

static int	*get_rund_num(void)
{
	const int	n = SIDE_PICTURE * SIDE_PICTURE;
	int			*rand_num;
	int			i;

	rand_num = (int *)malloc((sizeof(int) * n));
	i = 0;
	while (i < n)
	{
		rand_num[i] = i;
		i++;
	}
	shuffle(rand_num, n);
	return (rand_num);
}

static void	set_color(t_visualizer *vis, int *picture, int i)
{
	WIN->data[i / SIDE_PICTURE * SIZE_FIELD_X +
			i % SIDE_PICTURE] = picture[i];
}

int			rand_put_pixel(t_visualizer *vis, int *picture)
{
	const int	n = SIDE_PICTURE * SIDE_PICTURE;
	static int	*rand_num;
	static int	i;

	if (rand_num == NULL)
	{
		rand_num = get_rund_num();
		i = -1;
	}
	i++;
	while (i % 10000 != 0)
	{
		if (i >= n)
		{
			mlx_put_image_to_window(WIN->mlx, WIN->win, WIN->image, 0, 0);
			return (1);
		}
		set_color(vis, picture, rand_num[i]);
		i++;
	}
	if (i > n)
		return (1);
	set_color(vis, picture, rand_num[i]);
	mlx_put_image_to_window(WIN->mlx, WIN->win, WIN->image, 0, 0);
	return (0);
}
