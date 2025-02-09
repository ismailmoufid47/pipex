/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:38:20 by isel-mou          #+#    #+#             */
/*   Updated: 2025/02/09 19:11:54 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;

	pipex.argv = argv;
	pipex.argc = argc;
	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1... cmdn file2\n", 2);
		return (1);
	}
	if (argc < 6 && !ft_strcmp(argv[1], "here_doc"))
	{
		ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd1... cmdn file2\n", 2);
		return (1);
	}
	i = 2 + !ft_strcmp(argv[1], "here_doc");
	create_first_child(&pipex, argv[i], envp);
	while (++i < argc - 2)
		create_middle_child(&pipex, argv[i], envp);
	create_last_child(&pipex, argv[argc - 2], envp);
	while (wait(&pipex.status) > 0)
		;
	if (WIFEXITED(pipex.status))
		return (WEXITSTATUS(pipex.status));
	return (0);
}
