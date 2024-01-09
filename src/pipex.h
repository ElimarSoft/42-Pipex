/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala-ba <jsala-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:16:58 by jsala-ba          #+#    #+#             */
/*   Updated: 2024/01/09 15:02:59 by jsala-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define FDS_IN 0
# define FDS_OUT 1
# define FDS_PIPE_READ 2
# define FDS_PIPE_WRITE 3
# define FDS_IN_EXEC 4
# define FDS_OUT_EXEC 5
# define FDS_MAX 6
# define PATH_FILE_IN 0
# define PATH_FILE_OUT 1
# define PATH_FILE_MAX 2
# include "os.h"

typedef struct s_context
{
	char	*paths[PATH_FILE_MAX];
	char	*limitador;
	int		fds[FDS_MAX];
	char	***exec_args;
	char	**exec_paths;
	char	**env;
	int		argc;
	char	**argv;
	int		here_doc;
	int		*res;
}			t_context;

void		free_split(char **ptr);
char		*get_env(char **env, char *cmd);
void		process(t_context *cn);
void		free_mem(t_context *cn);
int			has_pad(char *str);
void		read_in(char *sep, int fd_out);
int			is_shcmd(char *str);
int			has_pad(char *str);
void		cfree(void *ptr);
void		process_parent_bonus(t_context *cn);
int			check_here_doc(t_context *cn);
#endif
