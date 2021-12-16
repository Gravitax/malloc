#include "main.h"

static bool chunk_is_free(t_zone *zone, int64_t page_head, int page_index) {
    t_chunk *chunk;
    int     i = 0;

    while (i < zone->chunks.nb_cells) {
        chunk = dyacc(&zone->chunks, i);
		if (chunk->page == page_index && chunk->addr == page_head)
			return (false);
		++i;
    }
    return (true);
}

static void *set_chunk(t_zone *zone, size_t size, t_page *page, int page_index) {
    t_chunk new_chunk;
    int64_t page_head;
    int64_t page_length;

    page_head   = page->addr;
    page_length = page_head + (int64_t)page_size();
    while (page_head < page_length) {
        if (chunk_is_free(zone, page_head, page_index) == true) {
            new_chunk.addr = page_head;
            new_chunk.size = size;
            new_chunk.page = page_index;
            new_chunk.zone = zone->id;
            if (dynarray_push(&zone->chunks, &new_chunk, false))
                return (NULL);
            --page->free_space;
            return((void *)page_head);
        }
        page_head += zone->chunks_size;
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
    if (dynarray_push(&zone->chunks, &new_chunk, false))
        return (NULL);
    return (addr);
}

void        *chunk_alloc(t_zone *zone, size_t size) {
    t_page  *page;
    int     i = 0;

    ft_printf(1, "chunk alloc\nzone->id: %d\n-----\n", (int)zone->id);

    if (zone->id == ZONE_LARGE)
        return (set_large_chunk(zone, size));
    while (i < zone->pages.nb_cells) {
        page = dyacc(&zone->pages, i);
        if (page->free_space > 0)
            return (set_chunk(zone, size, page, i));
        ++i;
    }
    // return (set_pages(zone, 1) ? NULL : chunk_alloc(zone, size))
    return (NULL);
}
