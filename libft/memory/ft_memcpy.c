/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marcaboye@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:46:05 by maboye            #+#    #+#             */
/*   Updated: 2021/12/22 11:39:08 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

// void			*ft_memcpy(void *dst, const void *src, size_t n)
// {
// 	char		*d;
// 	const char	*s;

// 	d = (char *)dst;
// 	s = (const char *)src;
// 	while (n--)
// 		*d++ = *s++;
// 	return (dst);
// }

void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

    if ((uintptr_t)dst % sizeof(long) == 0 &&
		(uintptr_t)src % sizeof(long) == 0 &&
		n % sizeof(long) == 0) {
            long *d = dst;
        	const long *s = src;

            for (i = 0; i < n / sizeof(long); i++)
                d[i] = s[i];
	}
    else {
        char *d = dst;
        const char *s = src;

        for (i = 0; i < n; i++)
            d[i] = s[i];
	}
    return (dst);
}

