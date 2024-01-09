/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala-ba <jsala-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 09:27:06 by jsala-ba          #+#    #+#             */
/*   Updated: 2023/09/16 09:27:06 by jsala-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#define MIN_VAL -2147483648

static void	ft_rec(char *buff, int *ptr, int n)
{
	if (n / 10 > 0)
		ft_rec(buff, ptr, n / 10);
	buff[(*ptr)++] = n % 10 + '0';
}

void	ft_putnbr_fd(int n, int fd)
{
	char	buff[16];
	int		ptr;

	ptr = 0;
	if (n == MIN_VAL)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		buff[ptr++] = '-';
	}
	ft_rec(buff, &ptr, n);
	write(fd, buff, ptr);
}
