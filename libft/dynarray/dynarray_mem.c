/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marcaboye@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 18:04:09 by gedemais          #+#    #+#             */
/*   Updated: 2021/12/22 11:03:36 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	realloc_content(t_dynarray *arr)
{
	void	*tmp;
	size_t	prev_size;

	prev_size = arr->byte_size;
	arr->byte_size *= 2;
	munmap(arr->tmp, prev_size);
	if (!(tmp = alloc_content((size_t)arr->byte_size))
		|| !(arr->tmp = alloc_content((size_t)arr->byte_size)))
		return (-1);
	ft_memcpy(tmp, arr->arr, prev_size);
	munmap(arr->arr, prev_size);
	arr->arr = tmp;
	return (0);
}

int			check_space(t_dynarray *arr)
{
	if (arr->nb_cells * arr->cell_size >= arr->byte_size) {
		if (realloc_content(arr))
			return (-1);
	}
	return (0);
}

void		*alloc_content(size_t size)
{
	size_t		new_size;
	int			pagesize;
	void		*ptr;


	pagesize = getpagesize();
	new_size = 0;
	while (new_size < size)
		new_size += (size_t)pagesize;
	ptr = mmap(NULL, new_size + 1,
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
}

int			dynarray_dump(t_dynarray *array, t_dynarray *dump)
{
	ft_memcpy(dump, array, sizeof(t_dynarray));
	if (!(dump->arr = alloc_content((size_t)dump->byte_size))
		|| !(dump->tmp = alloc_content((size_t)dump->byte_size)))
		return (-1);
	ft_memcpy(dump->arr, array->arr, (size_t)dump->byte_size);
	return (0);
}
