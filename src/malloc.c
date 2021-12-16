#include "main.h"

#include <stdio.h>

void        *malloc(size_t size) {
    
    ft_printf(1, "malloc start\nsize: %d\n----------\n", (int)size);

    if (*zones_are_init() == false && zones_init() == -1)
        return (NULL);

    // if (size < ZS_TINY)
    //     size = ZS_TINY;

    ft_printf(1, "zones initialized\n----------\n");

    // return (NULL);
    
    const size_t    sizes[ZONE_MAX + 1] = {0, ZS_TINY, ZS_SMALL, ZS_LARGE};
    unsigned int    i = 0;

    // if (size == 0)
    //     return (chunk_alloc(get_zone(0), size));
    while (i < ZONE_MAX) {
        if (size > sizes[i] && size <= sizes[i + 1]) {
            return (chunk_alloc(get_zone(i), size));
        }
        ++i;
    }
    return (NULL);
}
