#include <stdio.h>

void        *malloc(size_t size);

int         main() {
    int     i = 0;
    char    *addr;

    while (i < 1024) {
        addr    = (char *)malloc(1024);
        addr[0] = 42;
        ++i;
    }
    return (0);
}
