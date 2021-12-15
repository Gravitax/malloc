/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:45:34 by maboye            #+#    #+#             */
/*   Updated: 2020/08/08 16:23:52 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void			ft_convert_base(char *res, size_t val, char *base_to)
{
	size_t		len_base;
	int			i;

	len_base = ft_strlen(base_to);
	i = 0;
	if (val)
		while (val > 0)
		{
			res[i] = base_to[val % len_base];
			val /= len_base;
			++i;
		}
	else
		res[i++] = base_to[0];
	res[i] = '\0';
	ft_strrev(res);
}
