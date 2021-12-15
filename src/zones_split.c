void        *chunks_alloc(t_zone *zone, size_t size) {
    t_page          *page;
    unsigned int    i = 0;

    while (i < zone->pages.nb_cells) {
        page = dyacc(&zone->pages, (int)i);
        if (page->frees > 0)
            return (NULL);
        ++i;
    }
    return (NULL);
}

void		*zones_split(size_t size) {
    const size_t    sizes[ZONE_MAX + 1] = {0, ZS_TINY, ZS_SMALL, ZS_LARGE};
    unsigned int    i = 0;

    if (size == 0)
        return (chunks_alloc(get_zone(0), size));
    while (i < ZONE_MAX) {
        if (size > sizes[i] && size <= sizes[i + 1])
            return (chunks_alloc(get_zone(i), size));
        ++i;
    }
    return (NULL);
}
