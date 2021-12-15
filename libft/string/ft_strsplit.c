/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:37:46 by maboye            #+#    #+#             */
/*   Updated: 2020/08/10 20:39:33 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int		ft_copyin_tab(const char *s, char **split, char c, int *current)
{
	int		start;

	while (s[*current] && s[*current] == c)
		++(*current);
	start = *current;
	while (s[*current] && s[*current] != c)
		++(*current);
	*split = ft_strsub(s, start, *current - start);
	return (*split ? 0 : -1);
}

char			**ft_strsplit(const char *str, char c)
{
	char	**split;
	int		i;
	int		current;
	int		len;

	if (!str || (len = ft_wordcount(str, c)) < 1
		|| !(split = (char **)ft_memalloc(sizeof(char *) * (len + 1))))
		return (NULL);
	current = 0;
	i = -1;
	while (++i < len)
		if (ft_copyin_tab(str, split + i, c, &current))
		{
			ft_arrfree((void **)split);
			return (NULL);
		}
	return (split);
}
