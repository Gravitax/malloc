#include "../include/main.h"

int		main() {
	void	*addr = NULL;

	addr = malloc(0);
	addr = malloc(16);
	addr = malloc(1024);
	addr = malloc(1024 * 1024);
	show_alloc_mem();
	return (0);
}
