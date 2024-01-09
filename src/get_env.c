/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jsala-ba <jsala-ba@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2023/12/10 07:06:58 by jsala-ba          #+#    #+#             */
/*   Updated: 2023/12/10 07:06:58 by jsala-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "os.h"
#include "pipex.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#define PATH_LEN 5

void	free_split(char **ptr)
{
	int	n;

	n = 0;
	while (ptr[n])
	{
		free(ptr[n]);
		n++;
	}
	free(ptr);
}

static char	*get_last_path(char *str, char a)
{
	int	n;

	n = 0;
	while (str[n])
		n++;
	n--;
	while (n >= 0)
	{
		if (str[n] == a)
			return (str + n + 1);
		n--;
	}
	return (str);
}

static char	*check_file(char *path, char *cmd)
{
	char	*fname;
	char	*path2;

	cmd = get_last_path(cmd, '/');
	path2 = ft_strjoin(path, "/");
	fname = ft_strjoin(path2, cmd);
	free(path2);
	if (access(fname, F_OK) >= 0)
		return (fname);
	else
	{
		free(fname);
		return (NULL);
	}
}

static char	*get_path_data(char **env)
{
	int		n;
	char	*path_data;

	n = 0;
	path_data = NULL;
	while (env[n])
	{
		path_data = ft_strnstr(env[n], "PATH=", PATH_LEN);
		if (path_data)
			break ;
		n++;
	}
	return (path_data);
}

char	*get_env(char **env, char *cmd)
{
	int		n;
	char	*path_data;
	char	**path_array;
	char	*result;

	if (has_pad(cmd))
		return (NULL);
	path_data = get_path_data(env);
	if (!path_data)
		return (NULL);
	path_array = ft_split(path_data + PATH_LEN, ':');
	n = 0;
	while (path_array[n])
	{
		result = check_file(path_array[n], cmd);
		if (result)
			break ;
		n++;
	}
	free_split(path_array);
	return (result);
}
