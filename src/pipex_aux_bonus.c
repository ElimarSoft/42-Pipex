/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_aux_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala-ba <jsala-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:43:28 by jsala-ba          #+#    #+#             */
/*   Updated: 2024/01/08 16:18:51 by jsala-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

#define ITER 0
#define SEPL 1
#define DONE 2
#define ARR_SIZE 3

static void	init_vars(char *str, int *ints)
{
	int	n;

	n = 0;
	while (str[n])
		n++;
	ints[SEPL] = n;
	ints[ITER] = 0;
	ints[DONE] = 0;
}

static char	read_write(int fd_out)
{
	char	a;

	read(0, &a, 1);
	write(fd_out, &a, 1);
	return (a);
}

void	read_in(char *sep, int fd_out)
{
	char	a;
	int		n[ARR_SIZE];

	init_vars(sep, n);
	while (1)
	{
		a = read_write(fd_out);
		if (a == '\n')
		{
			if (n[ITER] == n[SEPL] && !n[DONE])
				break ;
			n[DONE] = 0;
			n[ITER] = 0;
		}
		if ((a == sep[n[ITER]]) && sep[n[ITER]])
			n[ITER]++;
		else
		{
			n[ITER] = 0;
			if (a != '\n')
				n[DONE] = 1;
		}
	}
	exit(EXIT_SUCCESS);
}

void	process_parent_bonus(t_context *cn)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		exit(errno);
	if (pid == 0)
		read_in(cn->limitador, cn->fds[FDS_PIPE_WRITE]);
	wait(&status);
	free_mem(cn);
	exit(status);
}

int	check_here_doc(t_context *cn)
{
	cn->limitador = NULL;
	if (ft_strncmp(cn->argv[1], "here_doc", 8) != 0)
		return (0);
	else
	{
		cn->limitador = cn->argv[2];
		return (1);
	}
}
