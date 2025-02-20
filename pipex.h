/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:20:56 by isel-mou          #+#    #+#             */
/*   Updated: 2025/02/09 19:07:10 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/wait.h>

typedef enum e_file_descriptors
{
	INFILE,
	OUTFILE
}	t_file_descriptors;

typedef enum e_pipe_descriptors
{
	READ,
	WRITE
}	t_pipe_descriptors;

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	int		pipefd[2];
	int		status;
}	t_pipex;

pid_t	create_first_child(t_pipex *pipex, char *cmd, char *envp[]);
pid_t	create_last_child(t_pipex *pipex, char *cmd, char *envp[]);

char	**ft_split_cmd(char *str, char c);
void	execute_cmd(char **args, char *envp[]);

void	dup_and_close(int fd1, int fd2, int fd3, int fd4);
void	handle_file_error(char *file);
void	handle_exec_error(char **cmd, char *error_msg, int status);

#endif