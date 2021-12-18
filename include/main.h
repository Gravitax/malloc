#ifndef MAIN_H
# define MAIN_H

# define MAX_NAME	21
# define MIN_ALLOC	100

# define DEBUG_FREE		false
# define DEBUG_MALLOC	false
# define DEBUG_REALLOC	false

# include <stdio.h>
# include <sys/resource.h>
# include <limits.h>
# include <assert.h>

# include "../libft/libft.h"

enum			e_zones
{
	ZONE_TINY,
	ZONE_SMALL,
	ZONE_LARGE,
	ZONE_MAX
};

enum			e_zone_size
{
	ZS_TINY		= 16,
	ZS_SMALL	= 1024,
	ZS_LARGE	= INT_MAX
};

typedef struct	s_chunk
{
	int64_t		addr;
	size_t		size;
	int			page;
	int			zone;
}				t_chunk;

typedef struct	s_page
{
	int64_t		addr;
	size_t		size;
	int			free_space;
}				t_page;

typedef struct	s_zone
{
	t_dynarray	pages;
	t_dynarray	chunks;
	char		name[MAX_NAME];
	size_t		chunks_size;
	int			chunks_total;
	int			id;
}				t_zone;

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);

void			show_alloc_mem();

// ZONES
t_zone			*get_zone(unsigned int index);
bool			*zones_are_init();
int             zones_init();
// PAGES
int				page_size();
int         	set_pages(t_zone *zone, unsigned int nb_pages);
// CHUNKS
void        	*chunk_alloc(t_zone *zone, size_t size);
t_chunk     	*chunk_find(t_zone **zone, int *index, void *ptr);
void        	chunk_free(t_zone *zone, t_chunk *chunk, int index);

bool			*debug();

#endif
