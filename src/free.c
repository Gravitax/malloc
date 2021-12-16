#include "main.h"

static int      zone_find(void *ptr) {
    t_zone  *zone;
    t_page  *page;
    int     i = 0;
    int     j;

    while (i < ZONE_LARGE) {
        j = 0;
        zone = get_zone(i);
        while (j < zone->pages.nb_cells) {
            page = dyacc(&zone->pages, j);
            if (ptr >= (void *)page->addr &&
                ptr < (void *)((size_t)page->addr + page->size))
                return (i);
            ++j;
        }
        ++i;
    }
    return (ZONE_LARGE);
}

t_chunk     *chunk_find(t_zone **zone, int *index, void *ptr) {
    t_zone  *z;
    t_chunk *chunk;
    int     i = 0;

    if (!(z = get_zone(zone_find(ptr))))
        return (NULL);
    while (i < z->chunks.nb_cells) {
        chunk = dyacc(&z->chunks, i);
        if (chunk->zone == z->id && chunk->addr == (int64_t)ptr) {
            *zone   = z;
            *index  = i;
            return (chunk);
        }
        ++i;
    }
    return (NULL);
}

void        chunk_free(t_zone *zone, t_chunk *chunk, int index) {
    t_page  *page;

    if (zone->id != ZONE_LARGE) {
        page = dyacc(&zone->pages, chunk->page);
        ++page->free_space;
    }
    else
        munmap((void *)chunk->addr, chunk->size);
    dynarray_extract(&zone->chunks, index);
} 

void        free(void *ptr) {
    t_zone  *zone;
    t_chunk *chunk;
    int     index;

    if (ptr == NULL || *zones_are_init() == false)
		return ;
    if ((chunk = chunk_find(&zone, &index, ptr)))
		chunk_free(zone, chunk, index);
}
