#include "../include/main.h"


// export LD_LIBRARY_PATH=/mnt/nfs/homes/maboye/workplace/malloc:$LD_LIBRARY_PATH
// make
// gcc -L"/mnt/nfs/homes/maboye/workplace/malloc" -o malloc correction/main.c -l"ft_mallocx86_64_Linux"
// ./malloc

int         main() {
    char    *str;
    int     i = 0;

    while (i < 1024) {
        str = (char *)malloc(1024);
        str[0] = 42;
        free(str);
        ++i;
    }
    return (0);
}
