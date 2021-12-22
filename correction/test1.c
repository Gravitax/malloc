#include "../include/main.h"

int		main() {
	char	*addr = NULL;
	int		i = 0;
	int		n = 1024;

	while (i <  n) {
		addr = (char *)malloc(1024);
		addr[0] = 42;
		++i;
	}
	return (0);
}
