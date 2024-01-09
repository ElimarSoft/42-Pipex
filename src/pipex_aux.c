/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala-ba <jsala-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:40:20 by jsala-ba          #+#    #+#             */
/*   Updated: 2024/01/09 15:03:14 by jsala-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "os.h"
#include "pipex.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void	free_mem(t_context *cn)
{
	int	n;
	int	m;

	n = 0;
	while (n < cn->argc - 3 - cn->here_doc)
	{
		cfree(cn->exec_paths[n]);
		if (cn->exec_args[n])
		{
			m = 0;
			while (cn->exec_args[n][m])
			{
				cfree(cn->exec_args[n][m]);
				m++;
			}
			cfree(cn->exec_args[n]);
		}
		n++;
	}
	cfree(cn->exec_args);
	cfree(cn->exec_paths);
	cfree(cn->res);
}

int	exec1(char *path, char **argv, int *fds, char **env)
{
	dup2(fds[FDS_IN_EXEC], 0);
	dup2(fds[FDS_OUT_EXEC], 1);
	if (fds[FDS_IN] > 2)
		close(fds[FDS_IN]);
	close(fds[FDS_OUT]);
	if (fds[FDS_PIPE_READ] > 2)
		close(fds[FDS_PIPE_READ]);
	close(fds[FDS_PIPE_WRITE]);
	if (path)
		execve(path, argv, env);
	_exit(errno);
}

static void	process_children(t_context *cn)
{
	int	n;
	int	cnt;
	int	pid;

	cnt = cn->argc - 3 - cn->here_doc;
	n = cnt - 1;
	while (n > 0)
	{
		if (n == cnt - 1)
			cn->fds[FDS_OUT_EXEC] = cn->fds[FDS_OUT];
		else
			cn->fds[FDS_OUT_EXEC] = cn->fds[FDS_PIPE_WRITE];
		if (pipe(cn->fds + FDS_PIPE_READ) == -1)
			exit(errno);
		cn->fds[FDS_IN_EXEC] = cn->fds[FDS_PIPE_READ];
		pid = fork();
		if (pid == -1)
			exit(errno);
		if (pid == 0)
			exec1(cn->exec_paths[n], cn->exec_args[n], cn->fds, cn->env);
		n--;
	}
}

static void	process_parent(t_context *cn)
{
	int	pid;
	int	status;

	cn->fds[FDS_IN_EXEC] = cn->fds[FDS_IN];
	cn->fds[FDS_OUT_EXEC] = cn->fds[FDS_PIPE_WRITE];
	pid = fork();
	if (pid == -1)
		exit(errno);
	if (pid == 0)
		exec1(cn->exec_paths[0], cn->exec_args[0], cn->fds, cn->env);
	wait(&status);
	free_mem(cn);
	exit(status);
}

void	process(t_context *cn)
{
	process_children(cn);
	if (cn->here_doc)
		process_parent_bonus(cn);
	else
		process_parent(cn);
}
