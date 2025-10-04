/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:22:15 by codespace         #+#    #+#             */
/*   Updated: 2025/10/04 14:22:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *cmd_path, char **cmd_args, char **envp)
{
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		perror("Execution error");
		exit(1);
	}
}

void	cleanup_pipex(t_pipex *pipex)
{
	if (pipex->paths)
		free_array(pipex->paths);
	if (pipex->cmd1_args)
		free_array(pipex->cmd1_args);
	if (pipex->cmd2_args)
		free_array(pipex->cmd2_args);
	if (pipex->cmd1_path && pipex->cmd1_path != pipex->cmd1_args[0])
		free(pipex->cmd1_path);
	if (pipex->cmd2_path && pipex->cmd2_path != pipex->cmd2_args[0])
		free(pipex->cmd2_path);
}
