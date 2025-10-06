/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 11:30:52 by codespace         #+#    #+#             */
/*   Updated: 2025/10/04 17:44:32 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_pipex *pipex, char **envp)
{
	close(pipex->pipe_fd[0]);
	if (pipex->infile == -1)
	{
		close(pipex->pipe_fd[1]);
		perror("Error");
		exit(1);
	}
	if (dup2(pipex->infile, STDIN_FILENO) == -1)
		error_exit("dup2");
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
		error_exit("dup2");
	close(pipex->infile);
	close(pipex->pipe_fd[1]);
	if (!pipex->cmd1_path)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(pipex->cmd1_args[0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	execute_command(pipex->cmd1_path, pipex->cmd1_args, envp);
}

void	parent_process(t_pipex *pipex, char **envp)
{
	close(pipex->pipe_fd[1]);
	if (pipex->outfile == -1)
	{
		close(pipex->pipe_fd[0]);
		perror("Error");
		exit(1);
	}
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
		error_exit("dup2");
	if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
		error_exit("dup2");
	close(pipex->pipe_fd[0]);
	close(pipex->outfile);
	if (!pipex->cmd2_path)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(pipex->cmd2_args[0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	execute_command(pipex->cmd2_path, pipex->cmd2_args, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	pid_t	pid;
	int		status;

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
	waitpid(pid, &status, 0);
	parent_process(&pipex, envp);
	cleanup_pipex(&pipex);
	return (0);
}
