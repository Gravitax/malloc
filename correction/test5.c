#include "../include/main.h"

int		main()
{
	void	*ptr = NULL;

	ptr = malloc(0);
	show_alloc_mem();
	return (0);
}
