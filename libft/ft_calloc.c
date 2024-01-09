/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala-ba <jsala-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 08:20:53 by jsala-ba          #+#    #+#             */
/*   Updated: 2024/01/03 08:21:11 by jsala-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	ft_bzero(void *ptr, size_t count)
{
	size_t			n;
	unsigned char	*ptr1;

	ptr1 = ptr;
	n = 0;
	while (n < count)
	{
		ptr1[n] = 0;
		n++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr)
	{
		ft_bzero(ptr, count * size);
	}
	return (ptr);
}
