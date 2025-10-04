/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 11:30:52 by codespace         #+#    #+#             */
/*   Updated: 2025/10/04 14:20:59 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_pipex *pipex, char **envp)
{
	close(pipex->pipe_fd[0]);
	if (pipex->infile == -1)
	{
		perror("Error opening infile");
		exit(1);
	}
	dup2(pipex->infile, STDIN_FILENO);
	dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	close(pipex->infile);
	close(pipex->pipe_fd[1]);
	execute_command(pipex->cmd1_path, pipex->cmd1_args, envp);
}

void	parent_process(t_pipex *pipex, char **envp)
{
	close(pipex->pipe_fd[1]);
	if (pipex->outfile == -1)
	{
		perror("Error opening outfile");
		exit(1);
	}
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->pipe_fd[0]);
	close(pipex->outfile);
	execute_command(pipex->cmd2_path, pipex->cmd2_args, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	pid_t	pid;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	init_pipex(&pipex, argv, envp);
	if (pipe(pipex.pipe_fd) == -1)
		error_exit("Pipe error");
	pid = fork();
	if (pid == -1)
		error_exit("Fork error");
	if (pid == 0)
		child_process(&pipex, envp);
	waitpid(pid, NULL, 0);
	parent_process(&pipex, envp);
	cleanup_pipex(&pipex);
	return (0);
}
