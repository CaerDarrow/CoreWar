#include "includes/libft.h"
#include <stdio.h>

int main()
{
	int *a = (int *)gc_memalloc(sizeof(int) * 228, "kek");

	*a = 228;
	ft_printf("%d\n", *a);
	gc(NULL, GC_ALL, GC_DEL);
}
