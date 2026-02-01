#include "cub3d.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		++start;
	if (end > 0)
	{
		end--;
		while (s1[end] && ft_strchr(set, s1[end]))
			end--;
	}
	if (start > end)
		return (ft_substr(s1, start, 0));
	trimmed = ft_substr(s1, start, end - start + 1);
	return (trimmed);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	strlen;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (start >= strlen)
		return (ft_strdup(""));
	if ((strlen - start) < len)
		len = strlen - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}

char *ft_strdup(const char *s)
{
    char *dup;
    int   len;
    int   i;

    len = 0;
    while (s[len])
        len++;

    dup = (char *)malloc(sizeof(char) * (len + 1));
    if (!dup)
        return (NULL);

    i = 0;
    while (i < len)
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';

    return (dup);
}

char *ft_strncpy(char *dst, const char *src, unsigned int n)
{
    unsigned int i;

    i = 0;
    while (i < n && src[i])
    {
        dst[i] = src[i];
        i++;
    }
    while (i < n)
    {
        dst[i] = '\0';
        i++;
    }
    return (dst);
}

#include <stddef.h>

size_t  ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t i;

    if (!dst || !src)
        return (0);

    i = 0;
    if (dstsize > 0)
    {
        while (i + 1 < dstsize && src[i])
        {
            dst[i] = src[i];
            i++;
        }
        dst[i] = '\0';
    }

    while (src[i])
        i++;

    return (i);
}

char *ft_strchr(const char *s, int c)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == (char)c)
            return ((char *)&s[i]);
        i++;
    }
    if (s[i] == (char)c)
        return ((char *)&s[i]);
    return (NULL);
}

int ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
    unsigned int i;

    if (n == 0)
        return (0);

    i = 0;
    while (i < n && s1[i] && s2[i])
    {
        if ((unsigned char)s1[i] != (unsigned char)s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }
    if (i < n)
        return ((unsigned char)s1[i] - (unsigned char)s2[i]);
    return 0;
}

static int	is_delim(char c, char d)
{
	return (c == d);
}

static int	count_words(char const *s, char d)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_delim(s[i], d))
			i++;
		if (s[i])
			count++;
		while (s[i] && !is_delim(s[i], d))
			i++;
	}
	return (count);
}

static void	free_all(char **tab, int i)
{
	while (i--)
		free(tab[i]);
	free(tab);
}


char	**ft_split(char const *s, char d)
{
	char	**tab;
	int		i;
	int		j;
	int		start;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_words(s, d) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && is_delim(s[i], d))
			i++;
		if (s[i])
		{
			start = i;
			while (s[i] && !is_delim(s[i], d))
				i++;
			tab[j] = ft_substr(s, start, i - start);
			if (!tab[j])
				return (free_all(tab, j), NULL);
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}
