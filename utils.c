/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 11:33:48 by codespace         #+#    #+#             */
/*   Updated: 2025/10/04 11:34:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **envp)
{
	while (*envp && ft_strnstr(*envp, "PATH=", 5) == 0)
		envp++;
	if (!*envp)
		return (NULL);
	return (ft_split(*envp + 5, ':'));
}

char	*find_command(char *cmd, char **paths)
{
	char	*part_path;
	char	*full_path;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (paths && *paths)
	{
		part_path = ft_strjoin(*paths, "/");
		full_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		paths++;
	}
	return (NULL);
}

void	child_process(char *cmd, char **envp, int *pipefd, int infile)
{
	char	**cmd_args;
	char	**paths;
	char	*cmd_path;

	dup2(infile, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	cmd_args = ft_split(cmd, ' ');
	paths = get_path(envp);
	cmd_path = find_command(cmd_args[0], paths);
	if (!cmd_path)
		error_exit("Command not found");
	execve(cmd_path, cmd_args, envp);
	error_exit("execve");
}

void	parent_process(char *cmd, char **envp, int *pipefd, int outfile)
{
	char	**cmd_args;
	char	**paths;
	char	*cmd_path;

	dup2(pipefd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	cmd_args = ft_split(cmd, ' ');
	paths = get_path(envp);
	cmd_path = find_command(cmd_args[0], paths);
	if (!cmd_path)
		error_exit("Command not found");
	execve(cmd_path, cmd_args, envp);
	error_exit("execve");
}
