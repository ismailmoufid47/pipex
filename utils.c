/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:38:03 by isel-mou          #+#    #+#             */
/*   Updated: 2025/02/08 19:37:35 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dup_and_close(int fd1, int fd2, int fd3, int fd4)
{
	dup2(fd1, fd2);
	dup2(fd3, fd4);
	close(fd1);
	close(fd3);
}

void	handle_file_error(char *file)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	exit(1);
}

void	handle_exec_error(char **cmd, char *error_msg, int status)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(*cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error_msg, 2);
	free(*cmd);
	exit(status);
}
