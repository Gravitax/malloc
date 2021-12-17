#include "../include/main.h"


// export LD_LIBRARY_PATH=/mnt/nfs/homes/maboye/workplace/malloc:$LD_LIBRARY_PATH
// make
// gcc -L"/mnt/nfs/homes/maboye/workplace/malloc" -o malloc correction/main.c -l"ft_mallocx86_64_Linux"
// ./malloc

int         main() {
    int     i = 0;

    while (i < 1024) {
        ++i;
    }
    return (0);
}
