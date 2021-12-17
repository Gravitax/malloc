#include "main.h"

int         set_pages(t_zone *zone, unsigned int nb_pages) {
    t_page          page;
    unsigned int    i = 0;

    while (i < nb_pages) {
        if (!(page.addr = (int64_t)alloc_content((size_t)page_size())))
            return (-1);
        page.size       = page_size();
        page.free_space = zone->chunks_total;
        if (dynarray_push(&zone->pages, &page, false))
            return (-1);
        ++i;
    }
    return (0);
}

static int  set_zone(t_zone *zone, bool is_large) {
    unsigned int    nb_pages;
    
    // MIN ALLOC doit etre divise par le nb de chunks afin de respecter min alloc
    nb_pages = is_large == true ? MIN_ALLOC : MIN_ALLOC / zone->chunks_total + 1;

    if (*debug()) {
        ft_printf(1, "-----\nset zone\n");
        ft_printf(1, "nb_pages: %d\n----------\n", (int)nb_pages);
    }

    // on cree les pages et les chunks pour chaque zones
    if (dynarray_init(&zone->pages, sizeof(t_page), nb_pages) == -1)
        return (-1);
    if (is_large == false && set_pages(zone, nb_pages) == -1)
        return (-1);
    if (dynarray_init(&zone->chunks, sizeof(t_chunk), MIN_ALLOC) == -1)
        return (-1);
    return (0);
}

int         zones_init() {
    const char		*names[ZONE_MAX]    = {"TINY", "SMALL", "LARGE"};
	const size_t	sizes[ZONE_MAX]     = {ZS_TINY, ZS_SMALL, ZS_LARGE};
    t_zone          *zone;
    unsigned int	i = 0;

    if (*debug()) {
        ft_printf(1, "zones init\n");
        ft_printf(1, "page_size: %d\n=====\n", page_size());
    }

    while (i < ZONE_MAX) {
        zone = get_zone(i);
        ft_strcpy(zone->name, names[i]);
		zone->id            = (int)i;
		zone->chunks_size   = sizes[i];
        zone->chunks_total  = page_size() / (int)zone->chunks_size;

        if (*debug()) {
            ft_printf(1, "id: %d\n", zone->id);
            ft_printf(1, "chunks size: %d\n", zone->chunks_size);
            ft_printf(1, "chunks total: %d\n", zone->chunks_total);
        }

        if (set_zone(zone, (i == ZONE_LARGE)) == -1)
            return (-1);
        ++i;
    }

    *zones_are_init() = true;
    return (0);
}
