/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakkoc < eakkoc@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:23:11 by eakkoc            #+#    #+#             */
/*   Updated: 2024/10/29 00:54:04 by eakkoc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	if (!dst && !src)
		return (NULL);
	if (dst < src)
	{
		d = (char *)dst;
		s = (const char *)src;
		while (len--)
			*d++ = *s++;
	}
	else
	{
		d = (char *)dst + len;
		s = (const char *)src + len;
		while (len--)
			*(--d) = *(--s);
	}
	return (dst);
}
