/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala-ba <jsala-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:57:01 by jsala-ba          #+#    #+#             */
/*   Updated: 2024/01/03 09:33:52 by jsala-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_shcmd(char *str)
{
	if (ft_strlen(str) == 4)
		if (!ft_strncmp(str, "exit", 4))
			return (1);
	return (0);
}

int	has_pad(char *str)
{
	int	n;

	n = 0;
	while (str[n])
	{
		if (str[0] == '/')
			return (1);
		else if (str[0] == ' ')
			break ;
		n++;
	}
	return (0);
}

void	cfree(void *ptr)
{
	if (ptr)
		free(ptr);
}
