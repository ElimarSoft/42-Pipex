/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala-ba <jsala-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:40:44 by jsala-ba          #+#    #+#             */
/*   Updated: 2024/01/08 16:21:02 by jsala-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "messages.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	get_args1(t_context *cn, int ind, char *data)
{
	char	**args;

	cn->exec_args[ind] = NULL;
	args = ft_split(data, ' ');
	if ((access(args[0], F_OK) < 0) && !is_shcmd(args[0]))
		cn->exec_paths[ind] = get_env(cn->env, args[0]);
	else
		cn->exec_paths[ind] = ft_strdup(args[0]);
	if (!cn->exec_paths[ind])
	{
		free_split(args);
		return (EXIT_FAILURE);
	}
	cn->exec_args[ind] = args;
	return (EXIT_SUCCESS);
}

int	open_in_file(t_context *cn, char **argv)
{
	int	fd;

	fd = 0;
	if (!cn->here_doc)
	{
		cn->paths[PATH_FILE_IN] = argv[1];
		fd = open(cn->paths[PATH_FILE_IN], O_RDONLY);
		cn->fds[FDS_IN] = fd;
	}
	return (fd);
}

int	create_variables(t_context *cn)
{
	int	n;
	int	fail_tot;
	int	cnt;

	cnt = cn->argc - 3 - cn->here_doc;
	open_in_file(cn, cn->argv);
	cn->exec_args = ft_calloc(cnt, sizeof(char **));
	cn->exec_paths = ft_calloc(cnt, sizeof(char *));
	cn->res = ft_calloc(cnt, sizeof(int));
	n = 0;
	fail_tot = 0;
	while (n < cnt)
	{
		cn->res[n] = get_args1(cn, n, cn->argv[n + 2 + cn->here_doc]);
		fail_tot = fail_tot + cn->res[n];
		n++;
	}
	if (fail_tot)
	{
		msg_command_not_found(cn->argv, cn->res, cnt);
	}
	return (EXIT_SUCCESS);
}

int	process_args(t_context *cn)
{
	int	n;
	int	write_options;

	cn->here_doc = check_here_doc(cn);
	if (cn->here_doc)
		write_options = O_CREAT | O_WRONLY | O_APPEND;
	else
		write_options = O_CREAT | O_WRONLY | O_TRUNC;
	cn->paths[PATH_FILE_OUT] = cn->argv[cn->argc - 1];
	cn->fds[FDS_OUT] = open(cn->paths[PATH_FILE_OUT], write_options, 0777);
	cn->fds[FDS_PIPE_WRITE] = cn->fds[FDS_OUT];
	if (cn->fds[FDS_OUT] < 0)
		return (print_error("bash"));
	else
	{
		n = 1 + 2 * cn->here_doc;
		while (n < cn->argc - 1)
		{
			if ((has_pad(cn->argv[n]) || n == 1) && access(cn->argv[n],
					F_OK) < 0)
				return (msg_file_not_found(cn->argv[n], cn->fds[FDS_OUT]));
			n++;
		}
	}
	return (create_variables(cn));
}

int	main(int argc, char **argv, char **env)
{
	t_context	context;
	t_context	*cn;

	cn = &context;
	cn->env = env;
	cn->argc = argc;
	cn->argv = argv;
	if (argc < 4)
		return (EXIT_FAILURE);
	if (process_args(cn) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	process(cn);
}
