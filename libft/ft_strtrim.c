/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakkoc < eakkoc@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:29:06 by eakkoc            #+#    #+#             */
/*   Updated: 2024/10/28 20:18:13 by eakkoc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
