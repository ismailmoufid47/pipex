/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:20:43 by isel-mou          #+#    #+#             */
/*   Updated: 2025/02/09 19:32:53 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.argv = argv;
	pipex.argc = argc;
	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	create_first_child(&pipex, argv[2], envp);
	create_last_child(&pipex, argv[argc - 2], envp);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(pipex.status))
		return (WEXITSTATUS(pipex.status));
	return (0);
}
