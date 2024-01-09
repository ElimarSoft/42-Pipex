/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jsala-ba <jsala-ba@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2023/10/14 12:09:32 by jsala-ba          #+#    #+#             */
/*   Updated: 2023/10/14 12:09:32 by jsala-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "messages.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MSG_000 "       0\n"
#define MSG_308 "     308\n"
#define MSG_LEN 9

int	msg_file_not_found(char *file, int fd)
{
	ft_putstr_fd(MSG_BASH, STD_ERROR);
	ft_putstr_fd(file, STD_ERROR);
	ft_putendl_fd(MSG_FILE_NOT_FOUND, STD_ERROR);
	write(fd, MSG_000, MSG_LEN);
	close(fd);
	return (EXIT_FAILURE);
}

int	msg_command_not_found(char **argv, int *res, int cnt)
{
	int	n;

	n = 0;
	while (n < cnt)
	{
		if (res[n])
		{
			ft_putstr_fd(MSG_CMD_NOT_FOUND, STD_ERROR);
			ft_putendl_fd(argv[n + 2], STD_ERROR);
		}
		n++;
	}
	return (EXIT_FAILURE);
}

int	print_error(char *str)
{
	perror(str);
	return (EXIT_FAILURE);
}
