#include "../include/main.h"


// export LD_LIBRARY_PATH=/mnt/nfs/homes/maboye/workplace/malloc:$LD_LIBRARY_PATH
// make
// gcc -L"/mnt/nfs/homes/maboye/workplace/malloc" -o malloc correction/main.c -l"ft_mallocx86_64_Linux"
// ./malloc

size_t      ft_strlen(const char *str);
void		ft_printf(int fd, const char *str, ...);

int         main() {
    char    *str    = NULL;
    int     i       = 0;
    int     n       = 1;

    while (i < n) {
        str = (char *)malloc(1024);
        str[0] = 42;
        free(str);
        ++i;
    }
    // ft_printf(1, "\nlength: %d\n%s\n", (int)ft_strlen(str), str);
    return (0);
}
