/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakkoc < eakkoc@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:38:16 by eakkoc            #+#    #+#             */
/*   Updated: 2024/10/29 00:56:18 by eakkoc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_all(char **result, int i)
{
	while (i-- > 0)
		free(result[i]);
	free(result);
}

static char	**words(char **result, char *s, char c)
{
	int		i;
	char	*start;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		start = s;
		while (*start && *start != c)
			start++;
		result[i] = ft_substr(s, 0, start - s);
		if (!result[i])
		{
			free_all(result, i);
			return (NULL);
		}
		i++;
		s = start;
	}
	result[i] = NULL;
	return (result);
}

static int	word_count(const char *s, char c)
{
	int	word;
	int	count;

	word = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && !count)
		{
			count = 1;
			word++;
		}
		else if (*s == c && *s)
		{
			count = 0;
		}
		s++;
	}
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		len;
	char	*tmp;

	tmp = (char *)s;
	len = word_count(s, c);
	str = (char **)malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (NULL);
	str = words(str, tmp, c);
	return (str);
}
