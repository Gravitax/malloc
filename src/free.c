#include "main.h"

void        free(void *ptr) {
    if (*zones_are_init() == false)
		return ;
    (void)ptr;
    return ;
}
