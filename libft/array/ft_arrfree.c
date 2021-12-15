/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 17:32:49 by maboye            #+#    #+#             */
/*   Updated: 2020/08/08 18:49:33 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void		ft_arrfree(void **add)
{
	int		i;
	int		len;

	len = ft_arrlen(add);
	i = -1;
	while (add && ++i < len)
		ft_memdel(add + i);
	free((void **)add);
	add = NULL;
}
