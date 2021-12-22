#include "../include/main.h"

static void	*new_allocation(size_t size) {
	const size_t    sizes[ZONE_MAX + 1] = {0, ZS_TINY, ZS_SMALL, ZS_LARGE};
    unsigned int    i = 0;

    while (i < ZONE_MAX) {
        if (size > sizes[i] && size <= sizes[i + 1])
            return (chunk_alloc(get_zone(i), size));
        ++i;
    }
    return (NULL);
}

void        *malloc(size_t size) {
    
    *debug() = DEBUG_MALLOC;
    if (*debug()) {
        ft_printf(1, "==========\n[[ MALLOC ]]\n");
        ft_printf(1, "size: %d\n==========\n", size);
    }

    if (size == 0)
        return (NULL);
    if (*zones_are_init() == false && zones_init() == -1)
        return (NULL);
    return (new_allocation(size));
}
