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
		index = rand() % 100;
		data = ft_int_get_mass(index);
		rb_push(t, data, index);
	}
}

void	list_add_all(t_list **t, int i)
{
	int	*num;
	int ind;
	while (i-- > 0) {
		ind = rand() % 10000;
		num = ft_int_get_mass(ind);
		ft_printf("Add: %d\n", ind);
		ld_push_back(t, num);
	}
}

void	list_to_rb_tree(t_list **l, t_rb_tree **t)
{
	t_list *temp = *l;
	int ind = 0;
	while (temp)
	{
		ind = *(int *)temp->data;
		rb_push(t, ft_int_get_mass(ind), ind);
		temp = temp->next;
	}
}

void	rb_tree_remove_check(t_rb_tree **t, t_list *list)
{
	int	i;
	t_list *l = l_last(list);
	while(l)
	{
		i = *(int *)l->data;
		if (!rb_find(*t, i))
		{
			ft_printf("Cant find value : %d\n", i);
			exit(-1);
		}
		l = l->prev;
	}
	l = l_last(list);
	while(l)
	{
		// ft_printf("Step 1\n");
		i = *(int *)l->data;
		if (i == 95)
			ft_printf("BREAK\n");
		if (rb_find(*t, i))
		{

			ft_printf("Remove: %d\n", i);
			rb_remove(t, i, &free);
		}
		else
		{
			ft_printf("Already removed: %d\n", i);
		}
		l = l->prev;
	}
}
void	array_as_list(t_list **l, ...)
{
	int i = 20, num = 0;;

	va_list ap;

	va_start(ap, l);
	while (i-- > 0)
	{
		ft_printf("Add ");
		ld_push_back(l, ft_int_get_mass((num = va_arg(ap, int))));
		ft_printf("%d\n", num);
	}
	va_end(ap);
}

int	main()
{
	t_rb_tree	*t;

	srand(time(NULL));
	t = 0;

	// add_n(&t, 5);
	t_list *l = 0;
	list_add_all(&l, 1000);
	// array_as_list(&l, 98, 80, 64, 11, 45, 95, 63, 59, 18 ,34, 35, 97, 44, 84, 99, 56, 91, 84, 28, 15);
	ft_printf(CYN"Step 1\n"RESET);
	list_to_rb_tree(&l,&t);
	ft_printf(CYN"Step 2\n"RESET);
	rb_tree_remove_check(&t, l);
	// ft_printf(CYN"Step 2\n"RESET);
	ft_printf(CYN"Check\n");
	ft_printf(t ? RED"Tree still exist\n"RESET : RED"Tree succesfully destroyed\n"RESET);
	if (t)
		while(l)
		{
			ft_printf("%d, ", *(int *)l->data);
			l = l->next;
		}
printf("\n");

	printf("%#4x\n", 0);
	// rb_print(t);
	// ft_printf("\n~~~~~~~~~~~~\n");
	//
	// // rb_print(t, 1);
	//
	// if (rb_find(t, 42))
	// 	ft_printf(RED"YES\n"RESET);
	// else
	// 	ft_printf(CYN"NO\n"RESET);
	// rb_remove(&t, 142, &int_destructor);
	// rb_remove(&t, 42, &int_destructor);
	// rb_remove(&t, 2, &int_destructor);
	// rb_remove(&t, 33, &int_destructor);
	// rb_remove(&t, 1, &int_destructor);
	// rb_remove(&t, 242, &int_destructor);
	// rb_remove(&t, 1, &int_destructor);
	// rb_remove(&t, 1, &int_destructor);
	// rb_remove(&t, 342, &int_destructor);
	// rb_remove(&t, 3, &int_destructor);
	// rb_remove(&t, 3, &int_destructor);
	//
	// ft_printf("\n~~~~~~~~~~~~\n");
	//
	// if (t &&t->parent)
	// 	ft_printf("\nWWWWWhat\n");
	// if (!is_valid_rb(t))
	// {
	// 	ft_printf("\n\nWTF\n"CYN"ERROR\n"RESET);
	// }
	// // ft_printf("~~~~~~~~~~~~\n");
	// //
	// // ft_printf("\n");
	// // // rb_rotate_left(&t->right);
	// // ft_printf("**********\n");
	// // ft_printf("**********\n");
	// // rb_print(t, 1);
	// // ft_printf("\nsize: %d\n", rb_size(t));
	// l_destroy(&l);
	// rb_destroy(&t, &free);
	return (0);
}
//gcc -Ilibft/includes libft/libft.a  libft/printf/libftprintf.a test.c
