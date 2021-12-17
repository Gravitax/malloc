#include "main.h"

static bool chunk_is_free(t_zone *zone, int64_t page_head, int page_index) {
    t_chunk *chunk;
    int     i = 0;

    // on verifie si laddr peut etre stockee sur la page ciblee
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

    *debug() ? ft_printf(1, "chunk\n-----\n") : 0;

    page_head   = page->addr;
    page_length = page_head + (int64_t)page_size();
    // on jump de page on page en verifiant si il y a des chunks libre
    while (page_head < page_length) {
        if (chunk_is_free(zone, page_head, page_index) == true) {
            new_chunk.addr = page_head;
            new_chunk.size = size;
            new_chunk.page = page_index;
            new_chunk.zone = zone->id;

            if (*debug()) {
                ft_printf(1, "zone id: %d\n", new_chunk.zone);
                ft_printf(1, "size: %d\n", new_chunk.size);
                ft_printf(1, "addr: %s\n", ft_itoa_base((int64_t)new_chunk.addr, 16));
                ft_printf(1, "page_index: %d\n", new_chunk.page);
            }

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
    
    // comme il ny a quun chunk une alloc simple suffit
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
        ft_printf(1, "addr: %s\n", ft_itoa_base((int64_t)new_chunk.addr, 16));
        ft_printf(1, "page_index: %d\n", new_chunk.page);
    }

    if (dynarray_push(&zone->chunks, &new_chunk, false))
        return (NULL);
    return (addr);
}

void        *chunk_alloc(t_zone *zone, size_t size) {
    t_page  *page;
    int     i = 0;

    *debug() ? ft_printf(1, "chunk alloc\nzone->id: %d\n----------\n", (int)zone->id) : 0;

    // si cest large il ny a quun seul chunk
    if (zone->id == ZONE_LARGE)
        return (set_large_chunk(zone, size));
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
