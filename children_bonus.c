/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:34:29 by isel-mou          #+#    #+#             */
/*   Updated: 2025/02/09 16:53:19 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*  
In the first child process:  
- We close the READ end of the pipe to prevent hanging.  
  If left open, the child might hang, waiting for it to be closed,  
  but it will remain open in the child itself.  
- We open the input file as standard input.  
- We open the WRITE end of the pipe as standard output.  
- Finally, we execute the command.  
*/
pid_t	create_first_child(t_pipex *pipex, char *cmd, char *envp[])
{
	pid_t	pid;
	int		in_fd;

	if (ft_strcmp(pipex->argv[1], "here_doc") == 0)
		handle_heredoc(pipex);
	if (pipe(pipex->pipefd) == -1)
		handle_exec_error(cmd, strerror(errno), 1);
	pid = fork();
	if (pid == 0)
	{
		close(pipex->pipefd[READ]);
		in_fd = open(pipex->argv[1], O_RDONLY);
		if (in_fd == -1)
			handle_file_error(pipex->argv[1]);
		dup_and_close(in_fd, STDIN_FILENO, pipex->pipefd[WRITE], STDOUT_FILENO);
		execute_cmd(ft_split_cmd(cmd, ' '), envp);
	}
	else if (pid == -1)
		handle_exec_error(cmd, strerror(errno), 1);
	else
		close(pipex->pipefd[WRITE]);
	return (pid);
}

/*  
In a middle child process:  
- We close the previous pipe's WRITE end to prevent hanging.  
	If left open, the child might hang, waiting for it to be closed,  
	but it will remain open in the child itself.  
- We close the new pipe's READ end to prevent hanging.  
	If left open, the child might hang, waiting for it to be closed,  
	but it will remain open in the child itself.
- We open the previous pipe's READ end as standard input.
- We open the new pipe's WRITE end as standard output.
- Finally, we execute the command.
*/
pid_t	create_middle_child(t_pipex *pipex, char *cmd, char *envp[])
{
	pid_t	pid;

	pipex->prev_pipefd[READ] = pipex->pipefd[READ];
	pipex->prev_pipefd[WRITE] = pipex->pipefd[WRITE];
	if (pipe(pipex->pipefd) == -1)
		handle_exec_error(cmd, strerror(errno), 1);
	pid = fork();
	if (pid == 0)
	{
		close(pipex->prev_pipefd[WRITE]);
		close(pipex->pipefd[READ]);
		dup_and_close(pipex->prev_pipefd[READ], 0, pipex->pipefd[WRITE], 1);
		execute_cmd(ft_split_cmd(cmd, ' '), envp);
	}
	else if (pid == -1)
		handle_exec_error(cmd, strerror(errno), 1);
	else
		close(pipex->pipefd[WRITE]);
	return (pid);
}

/*
In the last child process:
- We open the output file as standard output.
- We open the READ end of the pipe as standard input.
- Finally, we execute the command.
*/
pid_t	create_last_child(t_pipex *pipex, char *cmd, char *envp[])
{
	pid_t	pid;
	int		out_fd;

	pid = fork();
	if (pid == 0)
	{
		out_fd = O_WRONLY | O_CREAT | O_TRUNC;
		if (!ft_strcmp(pipex->argv[1], "here_doc"))
			out_fd = O_WRONLY | O_CREAT | O_APPEND;
		out_fd = open(pipex->argv[pipex->argc - 1], out_fd, 0644);
		if (out_fd == -1)
			handle_file_error(pipex->argv[pipex->argc - 1]);
		dup_and_close(pipex->pipefd[READ], STDIN_FILENO, out_fd, STDOUT_FILENO);
		execute_cmd(ft_split_cmd(cmd, ' '), envp);
	}
	else if (pid == -1)
		handle_exec_error(cmd, strerror(errno), 1);
	else
	{
		close(pipex->pipefd[READ]);
		waitpid(pid, &pipex->status, 0);
		if (!ft_strcmp(pipex->argv[1], "here_doc") && unlink("here_doc") == -1)
			handle_file_error("here_doc");
	}
	return (pid);
}
