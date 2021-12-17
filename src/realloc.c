#include "main.h"

static void	*new_allocation(t_zone *zone, t_chunk *chunk, int index, size_t size) {
	void	*ptr;

	if (!(ptr = malloc(size)))
		return (NULL);
	ft_memcpy(ptr, (void *)chunk->addr, chunk->size);
	chunk_free(zone, chunk, index);
	return (ptr);
}

static void	*addr_not_found(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
		return (NULL);
	ft_memset(ptr, 0, size);
	return (ptr);
}

void        *realloc(void *ptr, size_t size) {
	t_zone	*zone;
	t_chunk	*chunk;
	int		index;

	*debug() = true;
    *debug() ? ft_printf(1, "=====\nREALLOC\nsize: %d\n=====\n", (int)size) : 0;

	if (size == 0)
		return (NULL);
    if (*zones_are_init() == false && zones_init() == -1)
		return (NULL);

    if (ptr == NULL || !(chunk = chunk_find(ptr, &index, &zone))) {
		return (addr_not_found(size));
	}
	// if (size < zone->chunks_size || size > zone->chunks_size)
	if (size > zone->chunks_size)
		return (new_allocation(zone, chunk, index, size));
	else {
		chunk->size = size;
		return ((void *)chunk->addr);
	}
}
