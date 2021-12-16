#include "../include/main.h"

// make
// gcc -L"/mnt/nfs/homes/maboye/workplace/malloc" -o malloc correction/main.c -l"ft_mallocx86_64_Linux"
// ./malloc

int         main() {
    char    *str = malloc(10000025);
    int     i = 0;
    
    while (str && i < 2100) {
        str[i] = 'a';
        ++i;
    }
    str[i] = '\0';
    return (0);
}
