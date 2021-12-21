#include "../include/main.h"

static bool chunk_is_free(t_zone *zone, int64_t chunk_addr, int page_index) {
    t_chunk *chunk;
    int     i = 0;

    // on verifie si un chunk nest pas deja stocke sur chunk_addr
    while (i < zone->chunks.nb_cells) {
        chunk = dyacc(&zone->chunks, i);
        // si un chunk a lid de la page et que son addr est celle de chunk_addr
        // alors lemplacement est occupe
		if (chunk->page == page_index && chunk->addr == chunk_addr)
			return (false);
		++i;
    }
    return (true);
}

static void *set_chunk(t_zone *zone, size_t size, t_page *page, int page_index) {
    t_chunk new_chunk;
    int64_t chunk_addr;
    int64_t page_length;

    *debug() ? ft_printf(1, "chunk\n-----\n") : 0;

    chunk_addr  = page->addr;
    page_length = chunk_addr + (int64_t)page_size();
    // on avance le ptr de la page de chunk size
	// afin d'avancer de chunk en chunk
    while (chunk_addr < page_length) {
        if (chunk_is_free(zone, chunk_addr, page_index) == true) {
            new_chunk.addr = chunk_addr;
            new_chunk.size = size;
            new_chunk.page = page_index;
            new_chunk.zone = zone->id;

            if (*debug()) {
                ft_printf(1, "zone id: %d\n", new_chunk.zone);
                ft_printf(1, "size: %d\n", new_chunk.size);
                ft_printf(1, "addr: %d\n", (int64_t)new_chunk.addr);
                ft_printf(1, "page_index: %d\n", new_chunk.page);
            }

            if (dynarray_push(&zone->chunks, &new_chunk, false))
                return (NULL);
            --page->free_space;
            return((void *)chunk_addr);
        }
        chunk_addr += zone->chunks_size;
    }
    return (NULL);
}

static void *set_large_chunk(t_zone *zone, size_t size) {
    void    *addr;
    t_chunk new_chunk;

    if (!(addr = alloc_content(size)))
        return (NULL);
    new_chunk.addr = (int64_t)addr;
    new_chunk.size = size;
    new_chunk.page = zone->chunks.nb_cells;
    new_chunk.zone = zone->id;

    if (*debug()) {
        ft_printf(1, "large chunk\n-----\n");
        ft_printf(1, "zone id: %d\n", new_chunk.zone);
        ft_printf(1, "size: %d\n", new_chunk.size);
        ft_printf(1, "addr: %d\n", (int64_t)new_chunk.addr);
        ft_printf(1, "page_index: %d\n", new_chunk.page);
    }

    if (dynarray_push(&zone->chunks, &new_chunk, false))
        return (NULL);
    return (addr);
}

void        *chunk_alloc(t_zone *zone, size_t size) {
    t_page  *page;
    int     i = 0;

    *debug() ? ft_printf(1, "-----\nchunk alloc\nzone->id: %d\n-----\n", (int)zone->id) : 0;

    // si cest large pas besoin de parcourir les pages
    if (zone->id == ZONE_LARGE)
        return (set_large_chunk(zone, size));
    // on cherche une page avec un free space pour placer le chunk
    while (i < zone->pages.nb_cells) {
        page = dyacc(&zone->pages, i);
        if (page->free_space > 0)
            return (set_chunk(zone, size, page, i));
        ++i;
    }
    // si on arrive a ce stade aucun chunk na ete set
    // il ny a donc plus de free_space disponible
    // il faut donc creer une page et allouer le chunk
    return (set_pages(zone, 1) == -1 ? NULL : chunk_alloc(zone, size));
}
