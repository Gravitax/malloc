#include "main.h"

static int  set_pages_data(t_zone *zone, unsigned int nb_pages) {
    t_page          page;
    unsigned int    i = 0;

    while (i < nb_pages) {
        if (!(page.addr = (int64_t)alloc_content((size_t)page_size())))
            return (-1);
        page.size       = page_size();
        page.frees      = zone->chunks_total;
        if (dynarray_push(&zone->pages, &page, false))
            return (-1);
        ++i;
    }
    return (0);
}

static int  set_zone_data(t_zone *zone, bool is_large) {
    unsigned int    nb_pages;

    nb_pages = is_large == true ? MIN_ALLOC : MIN_ALLOC / zone->chunks_total + 1;
    if (dynarray_init(&zone->pages, sizeof(t_page), nb_pages) == -1)
        return (-1);
    if (is_large == false && set_pages_data(zone, nb_pages) == -1)
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

    while (i < ZONE_MAX) {
        zone = get_zone(i);
        ft_strcpy(zone->name, names[i]);
		zone->id            = (int)i;
		zone->chunks_size   = sizes[i];
        zone->chunks_total  = page_size() / (int)zone->chunks_size;
        if (set_zone_data(zone, (i == ZONE_LARGE)) == -1)
            return (-1);
        ++i;
    }
    *zones_are_init() = true;
    return (0);
}
