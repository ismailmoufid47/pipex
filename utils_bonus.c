/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:38:03 by isel-mou          #+#    #+#             */
/*   Updated: 2025/02/09 16:27:34 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	dup_and_close(int fd1, int fd2, int fd3, int fd4)
{
	dup2(fd1, fd2);
	dup2(fd3, fd4);
	close(fd1);
	close(fd3);
}

void	handle_heredoc(t_pipex *pipex)
{
	int		fd;
	char	*line;

	fd = open("here_doc", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		handle_file_error("here_doc");
	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		line[ft_strlen(line) - 1] = '\0';
		if (!ft_strcmp(line, pipex->argv[2]))
		{
			free(line);
			break ;
		}
		line[ft_strlen(line)] = '\n';
		ft_putstr_fd(line, fd);
		free(line);
	}
	close(fd);
}

void	handle_file_error(char *file)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	exit(1);
}

void	handle_exec_error(char *cmd, char *error_msg, int status)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error_msg, 2);
	exit(status);
}
