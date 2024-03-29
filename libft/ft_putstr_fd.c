/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala-ba <jsala-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 09:27:13 by jsala-ba          #+#    #+#             */
/*   Updated: 2023/09/16 09:27:13 by jsala-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "os.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	n;

	n = 0;
	while (s[n])
		n++;
	if (n)
		write(fd, s, n);
}
