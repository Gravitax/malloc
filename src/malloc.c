#include "main.h"

void        *malloc(size_t size) {
    (void)size;
    if (*zones_are_init() == false && zones_init() == -1)
        return (NULL);
    return (zones_split(size));
}
