#include <stdio.h>

void        *malloc(size_t size);
void        free(void *ptr);

int         main() {
    int     i = 0;
    char    *addr;

    while (i < 1024) {
        addr    = (char *)malloc(1024);
        addr[0] = 42;
        free(addr);
        ++i;
    }
    return (0);
}