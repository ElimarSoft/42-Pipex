/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala-ba <jsala-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:01:53 by jsala-ba          #+#    #+#             */
/*   Updated: 2023/09/16 10:42:01 by jsala-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_strlen(const char *str)
{
	int	n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*ptr;
	int		n;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = malloc(len1 + len2 + 1);
	if (!ptr)
		return (0);
	n = 0;
	while (n < len1)
	{
		ptr[n] = s1[n];
		n++;
	}
	n = 0;
	while (n < len2)
	{
		ptr[n + len1] = s2[n];
		n++;
	}
	ptr[len1 + len2] = 0;
	return (ptr);
}
