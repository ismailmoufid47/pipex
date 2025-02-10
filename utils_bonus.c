/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:38:03 by isel-mou          #+#    #+#             */
/*   Updated: 2025/02/10 20:40:27 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
