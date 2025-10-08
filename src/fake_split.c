/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:24:24 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/08/15 10:24:27 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_count_word(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			word++;
		i++;
	}
	return (word + 1);
}

static int	ft_size_word(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i])
	{
		size++;
		i++;
	}
	return (size);
}

char	**fake_split(char const *s, char c)
{
	int		i;
	int		word;
	char	**strs;
	int		j;

	i = 0;
	j = -1;
	word = ft_count_word(s, c);
	strs = (char **)safe_calloc((word + 1), sizeof(char *));
	while (++j < word)
	{
		strs[j] = safe_substr(s, i, ft_size_word(s, c, i));
		i += ft_size_word(s, c, i) + 1;
	}
	strs[j] = 0;
	return (strs);
}
