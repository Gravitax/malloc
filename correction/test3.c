#include "../include/main.h"

#define M (1024 * 1024)


// export LD_LIBRARY_PATH=/mnt/nfs/homes/maboye/workplace/malloc:$LD_LIBRARY_PATH
// make
// gcc -L"/mnt/nfs/homes/maboye/workplace/malloc" -o malloc correction/main.c -l"ft_mallocx86_64_Linux"
// ./malloc

void		ft_printf(int fd, const char *str, ...);
char		*ft_strcpy(char *dst, const char *src);

int         main() {
    char    *addr1;
    char    *addr2;

    addr1 = (char *)malloc(16 * M);
    ft_strcpy(addr1, "Bonjours\n");
    ft_printf(1, "%s", addr1);
    addr2 = (char *)realloc(addr1, 128 * M);
    addr2[127 * M] = 42;
    ft_printf(1, "%s", addr2);
    return (0);
}
