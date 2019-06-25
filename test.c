#include "libft.h"


void 	add(t_rb_tree **t, int index)
{
	int			*data;

	data = ft_int_get_mass(index);
	rb_push(t, data, index);

}
int	is_valid_rb(t_rb_tree *t)
{
	if (t)
	{
		if (!t->parent)
			return (is_valid_rb(t->left) && is_valid_rb(t->right));
		else
			return (!(t->clr == R && t->parent->clr == R) && is_valid_rb(t->left) && is_valid_rb(t->right));
	}
	return (1);
}

int	main()
{
	t_rb_tree	*t;
	int			*data;
	int			i;
	int			index;

	srand(time(NULL));
	t = 0;
	i = -1;
	while (++i < 3)
	{
		index = rand() % 1000;
		data = ft_int_get_mass(index);
		// ft_printf("%d ", index);
		// ft_printf("before (add %d):\n", index);
		// rb_print(t, 1);
		rb_push(&t, data, index);
		// ft_printf("after (add %d):\n", index);
		// rb_print(t, 1);
	}
	rb_print(t, 1);

	int *res = rb_find(t, 42);
	if (res)
		ft_printf(RED"%d\n"RESET, *res);
	else
		ft_printf(CYN"NO\n"RESET);

	ft_printf("\n~~~~~~~~~~~~\n");

	if (t->parent)
		ft_printf("\nWWWWWhat\n");
	if (!is_valid_rb(t))
	{
		ft_printf("\n\nWTF\n"CYN"ERROR\n"RESET);
	}
	// ft_printf("~~~~~~~~~~~~\n");
	//
	// ft_printf("\n");
	// // rb_rotate_left(&t->right);
	// ft_printf("**********\n");
	// ft_printf("**********\n");
	// rb_print(t, 1);
	// ft_printf("\nsize: %d\n", rb_size(t));
	return (0);
}
//gcc -Ilibft/includes libft/libft.a  libft/printf/libftprintf.a test.c
