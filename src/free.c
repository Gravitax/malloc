#include "main.h"

static int      zone_find(void *ptr) {
    t_zone  *zone;
    t_page  *page;
    int     i = 0;
    int     j;

    // on parcourt toutes les zones
    while (i < ZONE_LARGE) {
        j = 0;
        zone = get_zone(i);
        // on parcourt les pages
        while (j < zone->pages.nb_cells) {
            page = dyacc(&zone->pages, j);
            // si occurence on renvoit l'index de la zone
            if (ptr >= (void *)page->addr &&
                ptr < (void *)((size_t)page->addr + page->size))
                return (i);
            ++j;
        }
        ++i;
    }
    // si aucune occurence il faut encore verifier ZONE_LARGE car il ny a pas de page
    return (ZONE_LARGE);
}

t_chunk     *chunk_find(t_zone **zone, int *index, void *ptr) {
    t_zone  *z;
    t_chunk *chunk;
    int     i = 0;

    if (!(z = get_zone(zone_find(ptr))))
        return (NULL);

    if (*debug()) {
        ft_printf(1, "-----\nzone data\n");
        ft_printf(1, "chunk is in zone: %d\n", z->id);
        ft_printf(1, "chunks size: %d\n", z->chunks_size);
        ft_printf(1, "chunks total: %d\n", z->chunks_total);
        ft_printf(1, "nb chunks: %d\n", z->chunks.nb_cells);
        ft_printf(1, "nb page: %d\n", z->pages.nb_cells);
    }

    // on parcourt tout les chunks
    while (i < z->chunks.nb_cells) {
        chunk = dyacc(&z->chunks, i);

         if (*debug()) {
            ft_printf(1, "-----\nchunk data\n");
            ft_printf(1, "zone id: %d\n", chunk->zone);
            ft_printf(1, "size: %d\n", chunk->size);
            ft_printf(1, "addr: %d\n", chunk->addr);
            ft_printf(1, "page_index: %d\n-----\n", chunk->page);
        }

        // si il y a occurence on renvoit la zone, le chunk et son page_index
        if (chunk->zone == z->id && chunk->addr == (int64_t)ptr) {
            *zone   = z;
            *index  = i;

            if (*debug()) {
                ft_printf(1, "[[ chunk detected ]]\n-----\n");
            }

            return (chunk);
        }
        ++i;
    }
    *debug() ? ft_printf(1, "[[ no chunk found ]]\n-----\n") : 0;
    return (NULL);
}

void        chunk_free(t_zone *zone, t_chunk *chunk, int index) {
    t_page  *page;

    // si zone large alors pas de page il suffit de le unmap
    if (zone->id == ZONE_LARGE)
        munmap((void *)chunk->addr, chunk->size);
    else {
        // on actualise la page ou ce trouvait le chunk
        page = dyacc(&zone->pages, chunk->page);
        ++page->free_space;
    }
    // on supprime le chunk
    dynarray_extract(&zone->chunks, index);
} 

void        free(void *ptr) {
    t_zone  *zone;
    t_chunk *chunk;
    int     index;

    *debug() = DEBUG_FREE;
    if (*debug()) {
        ft_printf(1, "=====\nFREE\n");
        ft_printf(1, "ptr addr: %d\n=====\n", ptr);
    }

    if (ptr == NULL || *zones_are_init() == false)
		return ;
    if ((chunk = chunk_find(&zone, &index, ptr)))
		chunk_free(zone, chunk, index);
}
