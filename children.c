/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:34:29 by isel-mou          #+#    #+#             */
/*   Updated: 2025/02/10 21:06:14 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
In the first child process:
- We close the READ end of the pipe to prevent hanging.
  If left open, the child might hang, waiting for it to be closed,
  but it will remain open in the child itself.
- We open the input file as standard input.
- We open the WRITE end of the pipe as standard output.
- Finally, we execute the command.
*/
void	create_first_child(t_pipex *pipex, char *cmd, char *envp[])
{
	pid_t	pid;
	int		in_fd;

	if (pipe(pipex->pipefd) == -1)
		handle_exec_error(&cmd, strerror(errno), 1);
	pid = fork();
	if (pid == 0)
	{
		close(pipex->pipefd[READ]);
		in_fd = open_file(pipex, INFILE);
		if (in_fd == -1)
			handle_file_error(pipex->argv[1]);
		dup_and_close(in_fd, STDIN_FILENO, pipex->pipefd[WRITE], STDOUT_FILENO);
		execute_cmd(ft_split_cmd(cmd, ' '), envp);
	}
	else if (pid == -1)
		handle_exec_error(&cmd, strerror(errno), 1);
	else
		close(pipex->pipefd[WRITE]);
}

/*
In the last child process:
- We open the output file as standard output.
- We open the READ end of the pipe as standard input.
- Finally, we execute the command.
*/
void	create_last_child(t_pipex *pipex, char *cmd, char *envp[])
{
	pid_t	pid;
	int		out_fd;

	pid = fork();
	if (pid == 0)
	{
		close(pipex->pipefd[WRITE]);
		out_fd = open_file(pipex, OUTFILE);
		dup_and_close(pipex->pipefd[READ], STDIN_FILENO, out_fd, STDOUT_FILENO);
		execute_cmd(ft_split_cmd(cmd, ' '), envp);
	}
	else if (pid == -1)
		handle_exec_error(&cmd, strerror(errno), 1);
	else
	{
		waitpid(pid, &pipex->status, 0);
		close(pipex->pipefd[READ]);
		while (wait(NULL) > 0)
			;
	}
}
