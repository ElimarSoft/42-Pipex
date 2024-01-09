/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala-ba <jsala-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:54:04 by jsala-ba          #+#    #+#             */
/*   Updated: 2023/10/14 09:37:08 by jsala-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(char *haystack, const char *needle, size_t len)
{
	size_t	n;
	size_t	m;

	if (!needle[0])
		return (haystack);
	n = 0;
	while (haystack[n] && n < len)
	{
		m = 0;
		while ((haystack[n + m] == needle[m]) && haystack[n + m]
			&& (n + m < len))
		{
			m++;
		}
		if (!needle[m])
			return (haystack + n);
		n++;
	}
	return (0);
}
