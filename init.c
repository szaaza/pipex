/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 11:38:57 by codespace         #+#    #+#             */
/*   Updated: 2025/10/04 17:44:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_paths(char **envp)
{
	int		i;
	char	*path_line;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
			&& envp[i][2] == 'T' && envp[i][3] == 'H'
			&& envp[i][4] == '=')
		{
			path_line = envp[i] + 5;
			paths = ft_split(path_line, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **paths)
{
	int		i;
	char	*path;
	char	*tmp;

	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	init_pipex(t_pipex *pipex, char **argv, char **envp)
{
	pipex->infile = open(argv[1], O_RDONLY);
	pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipex->paths = get_paths(envp);
	pipex->cmd1_args = ft_split(argv[2], ' ');
	pipex->cmd2_args = ft_split(argv[3], ' ');
	pipex->cmd1_path = NULL;
	pipex->cmd2_path = NULL;
	if (pipex->cmd1_args && pipex->cmd1_args[0])
	{
		pipex->cmd1_path = find_command_path(pipex->cmd1_args[0],
				pipex->paths);
	}
	if (pipex->cmd2_args && pipex->cmd2_args[0])
	{
		pipex->cmd2_path = find_command_path(pipex->cmd2_args[0],
				pipex->paths);
	}
}
