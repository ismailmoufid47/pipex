/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:36:41 by isel-mou          #+#    #+#             */
/*   Updated: 2025/02/09 19:34:53 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd_path(char *cmd, char *envp[])
{
	char	*cmd_path;
	char	**path;
	int		i;

	i = 0;
	if (cmd && !access(cmd, X_OK))
		return (cmd);
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		envp[i] = "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
	i = ((path = ft_split(envp[i] + 5, ':')), 0);
	while (path[i++])
	{
		path[i - 1] = ((cmd_path = path[i - 1]), ft_strjoin(path[i - 1], "/"));
		free(cmd_path);
	}
	i = 0;
	cmd_path = ft_strjoin(path[i], cmd);
	while (path[i] && cmd_path && access(cmd_path, X_OK))
		cmd_path = ((free(cmd_path)), ft_strjoin(path[i++], cmd));
	if (cmd_path && !access(cmd_path, X_OK))
		return (cmd_path);
	return (free(cmd_path), (ft_free_split(path)), NULL);
}

void	execute_cmd(char **args, char *envp[])
{
	char	*cmd_path;

	cmd_path = get_cmd_path(args[0], envp);
	if (!cmd_path)
	{
		cmd_path = ft_strdup(args[0]);
		ft_free_split(args);
		handle_exec_error(&cmd_path, "command not found", 127);
	}
	if (execve(cmd_path, args, envp) == -1)
	{
		free(cmd_path);
		if (errno == EACCES)
			handle_exec_error(&args[0], "permission denied", 126);
		else
			handle_exec_error(&args[0], strerror(errno), 1);
		free(args);
	}
	handle_exec_error(&args[0], strerror(errno), 127);
}
