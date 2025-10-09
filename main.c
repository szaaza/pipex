/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 11:30:52 by codespace         #+#    #+#             */
/*   Updated: 2025/10/09 21:42:04 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_executable_path(char *path_env, char **cmd_args, int index)
{
	char	*path_with_slash;
	char	*full_cmd_path;
	char	**path_directories;

	path_directories = ft_split(path_env, ':');
	while (path_directories[index])
	{
		path_with_slash = ft_strjoin(path_directories[index], "/");
		full_cmd_path = ft_strjoin(path_with_slash, cmd_args[0]);
		free(path_with_slash);
		if (access(full_cmd_path, X_OK | F_OK) == 0)
		{
			ft_freestr(path_directories, 0);
			return (full_cmd_path);
		}
		free(full_cmd_path);
		index++;
	}
	ft_freestr(path_directories, 0);
	return (cmd_args[0]);
}

void	execute_command(char *command, char **envp, int env_index)
{
	char	*executable_path;
	char	*path_env;
	char	**cmd_args;

	cmd_args = ft_split(command, ' ');
	while (envp[++env_index])
	{
		if (ft_strncmp(envp[env_index], "PATH", 4) == 0)
			break ;
	}
	path_env = envp[env_index] + 5;
	executable_path = find_executable_path(path_env, cmd_args, 0);
	if (execve(executable_path, cmd_args, envp) == -1)
	{
		ft_putstr_fd(RED "COMMAND NOT FOUND.", 2);
		write(2, "\n", 1);
		ft_freestr(cmd_args, 0);
		exit(127);
	}
}

void	execute_first_command(int pipe_fds[], char **argv, char **envp)
{
	int	infile_fd;

	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd < 0)
		ft_error();
	dup2(pipe_fds[1], STDOUT_FILENO);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	execute_command(argv[2], envp, -1);
}

void	execute_second_command(int pipe_fds[], char **argv, char **envp)
{
	int		outfile_fd;
	pid_t	second_pid;
	int		exit_status;

	outfile_fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile_fd < 0)
		ft_error();
	second_pid = fork();
	if (second_pid == -1)
		ft_error();
	if (second_pid == 0)
	{
		dup2(pipe_fds[0], STDIN_FILENO);
		dup2(outfile_fd, STDOUT_FILENO);
		close(pipe_fds[1]);
		execute_command(argv[3], envp, -1);
	}
	close(pipe_fds[1]);
	close(outfile_fd);
	waitpid(second_pid, &exit_status, 0);
	if (WIFEXITED(exit_status))
		exit(WEXITSTATUS(exit_status));
	else
		exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fds[2];
	pid_t	first_pid;

	if (argc != 5)
	{
		ft_putendl_fd(RED "BAD ARGUMENTS", STDERR_FILENO);
		exit(1);
	}
	if (pipe(pipe_fds) == -1)
		ft_error();
	first_pid = fork();
	if (first_pid == -1)
		ft_error();
	if (first_pid == 0)
		execute_first_command(pipe_fds, argv, envp);
	else
	{
		execute_second_command(pipe_fds, argv, envp);
		waitpid(first_pid, NULL, 0);
	}
	return (0);
}
