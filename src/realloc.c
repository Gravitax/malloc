#include "../include/main.h"

static void	*new_allocation(t_zone *zone, t_chunk *chunk, int index, size_t size) {
	void	*ptr;

	if (!(ptr = malloc(size)))
		return (NULL);

	*debug() ? ft_printf(1, "[[ new allocation ]]\nnew ptr: %d\n", (int64_t)ptr) : 0;

	ft_memcpy(ptr, (void *)chunk->addr, chunk->size < size ? chunk->size : size);
	chunk_free(zone, chunk, index);
	return (ptr);
}

static void	*addr_not_found(size_t size) {
	void	*ptr;

	*debug() ? ft_printf(1, "[[ addr not found ]]\n") : 0;
	if (!(ptr = malloc(size)))
		return (NULL);
	ft_memset(ptr, 0, size);
	return (ptr);
}

static bool	addr_in_chunks(int64_t addr) {
	t_zone			*zone;
	t_chunk			*chunk;
	unsigned int	i = 0;
	int				j;

	*debug() ? ft_printf(1, "[[ addr already in chunks ]]\n") : 0;
	// si on demande a realloc ptr + 5
	// pour ne pas ecraser lallocation de ptr
	// il faut verifier si ptr est deja dans un chunk
	// si cest le cas cest une erreure
	while (i < ZONE_MAX) {
		j = 0;
		zone = get_zone(i);
		while (j < zone->chunks.nb_cells) {
			chunk = dyacc(&zone->chunks, j);
			if (addr >= chunk->addr && addr <= chunk->addr + (int64_t)chunk->size)
				return (true);
			++j;
		}
		++i;
	}
	return (false);
}

void        *realloc(void *ptr, size_t size) {
	t_zone	*zone;
	t_chunk	*chunk;
	int		index;

	*debug() = DEBUG_REALLOC;
	if (*debug()) {
		ft_printf(1, "=====\nREALLOC\nsize: %d\n", (int)size);
		ft_printf(1, "ptr addr: %d\n=====\n", (int64_t)ptr);
	}

    if (*zones_are_init() == false && zones_init() == -1)
		return (NULL);
	if (size == 0) {
		free(ptr);
		return (NULL);
	}
    if (ptr == NULL || !(chunk = chunk_find(&zone, &index, ptr)))
		return (addr_in_chunks((int64_t)ptr) ? NULL : addr_not_found(size));
	// if (size == zone->chunks_size) {
	// 	chunk->size = size;
	// 	return ((void *)chunk->addr);
	// }
	return (new_allocation(zone, chunk, index, size));
}
