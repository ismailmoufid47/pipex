/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:38:03 by isel-mou          #+#    #+#             */
/*   Updated: 2025/02/10 21:03:46 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(t_pipex *pipex, int file)
{
	int	fd;

	fd = O_WRONLY | O_CREAT | O_TRUNC;
	if (file == INFILE)
	{
		fd = open(pipex->argv[1], O_RDONLY);
		if (fd == -1)
			handle_file_error(pipex->argv[1]);
	}
	else if (file == OUTFILE)
	{
		fd = open(pipex->argv[pipex->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			handle_file_error(pipex->argv[pipex->argc - 1]);
	}
	else if (file == HERE_DOC)
	{
		if (!ft_strcmp(pipex->argv[1], "here_doc"))
			fd = O_WRONLY | O_CREAT | O_APPEND;
		fd = open(pipex->argv[pipex->argc - 1], fd, 0644);
		if (fd == -1)
			handle_file_error(pipex->argv[pipex->argc - 1]);
	}
	return (fd);
}

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
