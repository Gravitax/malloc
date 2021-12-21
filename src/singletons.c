#include "../include/main.h"

int		page_size() {
	static int	page_size = 0;

	if (page_size == 0)
		page_size = getpagesize();
	return (page_size);
}

t_zone	*get_zone(unsigned int index) {
	static t_zone	zones[ZONE_MAX];

	return (index >= ZONE_MAX ? NULL : &zones[index]);
}

bool	*zones_are_init() {
	static bool	var = false;

	return (&var);
}

bool	*debug() {
	static bool	value = false;

	return (&value);
}
