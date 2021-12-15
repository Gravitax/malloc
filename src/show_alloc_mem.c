#include "main.h"

// static int	addresses_sort_func(void *cell_a, void *cell_b)
// {
// 	const t_chunk	*a = cell_a;
// 	const t_chunk	*b = cell_b;
// 	int64_t			offset;

// 	offset = a->addr - b->addr;
// 	if (offset != 0)
// 		return (offset < 0 ? -1 : 1);
// 	return (0);
// }

// static void	print_zone_title(t_zone *zone)
// {
// 	char	addr[32];
// 	char	display[32];

// 	ft_putstr(zone->name);
// 	ft_putstr(" : ");
// 	ft_convert_base(addr, (size_t)zone->pages.arr, "0123456789ABCDEF");
// 	ft_strcpy(display, "0x");
// 	ft_strcat(display, &addr[4]);
// 	ft_putendl(display);
// 	fflush(stdout);
// }

// static void	print_chunk(size_t start_addr, size_t end_addr, size_t size)
// {
// 	char	start[32];
// 	char	end[32];
// 	char	s[16];
// 	char	display[128];

// 	ft_convert_base(start, start_addr, "0123456789ABCDEF");
// 	ft_convert_base(end, end_addr, "0123456789ABCDEF");
// 	ft_convert_base(s, size, "0123456789");
	
// 	ft_strcpy(display, "0x");
// 	ft_strcat(display, &start[4]);
// 	ft_strcat(display, " - ");
// 	ft_strcat(display, "0x");
// 	ft_strcat(display, &end[4]);
// 	ft_strcat(display, " : ");
// 	ft_strcat(display, s);
// 	ft_strcat(display, " octets");

// 	ft_putendl(display);
// }

// static void	print_zone_chunks(t_zone *zone, int *total)
// {
// 	t_dynarray	dump;
// 	t_chunk		*chunk;

// 	if (dynarray_dump(&zone->chunks, &dump))
// 		return ;
// 	dynarray_bubblesort(&dump, addresses_sort_func);
// 	for (int i = 0; i < dump.nb_cells; i++)
// 	{
// 		chunk = dyacc(&dump, i);
// 		*total += chunk->size;
// 		print_chunk((size_t)chunk->addr, (size_t)chunk->addr + chunk->size, chunk->size);
// 	}
// 	dynarray_free(&dump);
// }

// void	    show_alloc_mem(void)
// {
// 	t_zone	*zone;
// 	int		total = 0;

// 	for (unsigned int i = 0; i < ZONE_MAX; i++)
// 	{
// 		zone = g_zones(i);
// 		print_zone_title(zone);
// 		print_zone_chunks(zone, &total);
// 	}
// }
