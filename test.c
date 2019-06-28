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
void		int_destructor(void *t)
{
	free(t);
}
void		add_n(t_rb_tree **t, int n)
{
	int			index;
	int			*data;
	int			i;

	i = -1;
	while (++i < n)
	{
		index = rand() % 1000;
		data = ft_int_get_mass(index);
		rb_push(t, data, index);
	}
}

int	main()
{
	t_rb_tree	*t;

	srand(time(NULL));
	t = 0;

	// add_n(&t, 5);
	add(&t, 142);
	add(&t, 242);
	add(&t, 342);
	add(&t, 1);
	add(&t, 2);
	add(&t, 3);
	add(&t, 42);
	add(&t, 33);

	rb_print(t);
	ft_printf("\n~~~~~~~~~~~~\n");

	// rb_print(t, 1);

	if (rb_find(t, 42))
		ft_printf(RED"YES\n"RESET);
	else
		ft_printf(CYN"NO\n"RESET);
	rb_remove(&t, 142, &int_destructor);
	rb_remove(&t, 42, &int_destructor);
	rb_remove(&t, 2, &int_destructor);
	rb_remove(&t, 33, &int_destructor);
	rb_remove(&t, 1, &int_destructor);
	rb_remove(&t, 242, &int_destructor);
	rb_remove(&t, 1, &int_destructor);
	rb_remove(&t, 1, &int_destructor);
	rb_remove(&t, 342, &int_destructor);
	rb_remove(&t, 3, &int_destructor);
	rb_remove(&t, 3, &int_destructor);

	ft_printf("\n~~~~~~~~~~~~\n");

	if (t &&t->parent)
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
	rb_destroy(&t, &free);
	return (0);
}
//gcc -Ilibft/includes libft/libft.a  libft/printf/libftprintf.a test.c
