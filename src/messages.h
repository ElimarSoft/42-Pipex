/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala-ba <jsala-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:09:54 by jsala-ba          #+#    #+#             */
/*   Updated: 2024/01/08 16:19:58 by jsala-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H
# define STD_ERROR 2
# define MSG_CMD_NOT_FOUND "command not found: "
# define MSG_CANNOT_OPEN "cannot open "
# define MSG_FILE_NOT_FOUND ": No such file or directory"
# define MSG_BASH "-bash: "

int	msg_file_not_found(char *file, int fd);
int	msg_command_not_found(char **argv, int *res, int cnt);
int	print_error(char *str);
#endif
