#include "main.h"

#include <stdio.h>

void        *malloc(size_t size) {
    
    *debug() = false;
    *debug() ? ft_printf(1, "=====\nMALLOC\nsize: %d\n=====\n", (int)size) : 0;

    if (size == 0)
        return (NULL);
    if (*zones_are_init() == false && zones_init() == -1)
        return (NULL);
    
    const size_t    sizes[ZONE_MAX + 1] = {0, ZS_TINY, ZS_SMALL, ZS_LARGE};
    unsigned int    i = 0;

    while (i < ZONE_MAX) {
        if (size > sizes[i] && size <= sizes[i + 1]) {
            return (chunk_alloc(get_zone(i), size));
        }
        ++i;
    }
    return (NULL);
}
