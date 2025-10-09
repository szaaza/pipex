/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 11:33:48 by codespace         #+#    #+#             */
/*   Updated: 2025/10/09 21:55:30 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_s;
	void	*tmp1;
	char	*s;

	total_s = count * size;
	if (total_s < count && total_s < size)
		return (NULL);
	tmp1 = malloc(total_s);
	if (!tmp1)
		return (NULL);
	s = (char *)tmp1;
	if (tmp1 != 0)
	{
		while (total_s--)
		{
			*s = 0;
			s++;
		}
	}
	return (tmp1);
}

size_t	ft_total_words(char const *str, char c1)
{
	size_t	nw;

	nw = 0;
	if (*str == '\0' || !str)
		return (0);
	else if (c1 == '\0')
		return (1);
	while (*str != '\0')
	{
		if (*str != c1)
		{
			while (*str != c1 && *str != '\0')
				str++;
			nw++;
		}
		if (*str != '\0')
			str++;
	}
	return (nw);
}

static void	wword(char c, char *array, char const *s)
{
	size_t	i1;

	i1 = 0;
	while (s[i1] != '\0' && s[i1] != c)
	{
		array[i1] = s[i1];
		i1++;
	}
	array[i1] = '\0';
}

int	search_str(char c, char const *s, char **array)
{
	size_t	w_len;
	size_t	nw;
	size_t	i2;

	i2 = 0;
	nw = 0;
	while (s[i2])
	{
		if (s[i2] == c)
			i2++;
		else
		{
			w_len = 0;
			while (s[i2 + w_len] && s[i2 + w_len] != c)
				w_len++;
			array[nw] = (char *)ft_calloc((w_len + 1), sizeof(char));
			if (array[nw] == NULL)
				return (free_str2(array, nw));
			wword(c, array[nw], s + i2);
			i2 = i2 + w_len;
			nw++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	nw;
	char	**result1;

	if (!s)
		return (NULL);
	nw = ft_total_words(s, c);
	result1 = (char **)ft_calloc((nw + 1), sizeof(result1));
	if (result1 == NULL)
		return (NULL);
	if (search_str(c, s, result1) == 0)
		return (NULL);
	result1[nw] = NULL;
	return (result1);
}
