#include "libft.h"

int	main()
{
	t_rb_tree	*t;
	int			*data;
	int			i;
	int			index;

	srand(time(NULL));
	t = 0;
	i = -1;
	while (++i < 12)
	{
		index = rand() % 100;
		data = ft_int_get_mass(index);
		rb_push(&t, data, index);
	}
	rb_print(t, 1);
	rb_rotate_left(&t->right);
	ft_printf("**********\n");
	ft_printf("**********\n");
	rb_print(t, 1);
	ft_printf("\nsize: %d\n", rb_size(t));
	return (0);
}
//gcc -Ilibft/includes libft/libft.a  libft/printf/libftprintf.a test.c
