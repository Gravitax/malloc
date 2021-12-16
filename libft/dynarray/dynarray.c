/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 18:02:41 by gedemais          #+#    #+#             */
/*   Updated: 2021/12/16 19:57:01 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void			*dyacc(t_dynarray *arr, int index)
{
	if (index > arr->nb_cells || index < 0)
		return (NULL);
	return ((void *)(arr->arr + (index * arr->cell_size)));
}

void			dynarray_free(t_dynarray *arr)
{
	munmap(arr->arr, arr->byte_size);
	munmap(arr->tmp, arr->byte_size);
	ft_memset(arr, 0, sizeof(t_dynarray));
}

static int		start_size(int size)
{
	int	a;

	a = 2;
	while (size >= a)
		a += a;
	return (a);
}

int				dynarray_init(t_dynarray *arr, int cell_size, int nb_cells)
{
	if (cell_size <= 0 || nb_cells < 0)
		return (-1);
	arr->cell_size = cell_size;
	arr->nb_cells = 0;
	arr->byte_size = start_size(cell_size * nb_cells + 1);
	if (arr->byte_size > 0
		&& (!(arr->arr = alloc_content(arr->byte_size))
		|| !(arr->tmp = alloc_content(arr->byte_size))))
		return (-1);
	ft_memset(arr->arr, 0, arr->byte_size);
	return (0);
}
