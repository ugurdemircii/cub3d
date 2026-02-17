/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakkoc < eakkoc@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:21:52 by eakkoc            #+#    #+#             */
/*   Updated: 2024/10/28 16:18:11 by eakkoc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((char *)&ptr[i]);
		i++;
	}
	return (NULL);
}
