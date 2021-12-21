#include <string.h>
#include <unistd.h>

#include "../include/main.h"

#define M (1024 * 1024) 

void	print(char *s) {
	write(1, s, strlen(s));
}

int		main() {
	char	*addr1 = NULL;
	char	*addr3 = NULL;

	addr1 = (char *)malloc(16 * M);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr3 = (char *)realloc(addr1, 128 * M);
	addr3[127 * M] = 42;
	print(addr3);
	return (0);
}
