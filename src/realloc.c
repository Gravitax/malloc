#include "main.h"

void        *realloc(void *ptr, size_t size) {
    if (*zones_are_init() == false && zones_init() == -1)
		return (NULL);
	if (size == 0)
		free(ptr);
    return (NULL);
}
