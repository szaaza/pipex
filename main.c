/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 11:30:52 by codespace         #+#    #+#             */
/*   Updated: 2025/10/04 11:30:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		infile;
	int		outfile;

	if (argc != 5)
		error_exit("Usage: ./pipex file1 cmd1 cmd2 file2");

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		error_exit(argv[1]);
	outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile < 0)
		error_exit(argv[4]);
	if (pipe(fd) == -1)
		error_exit("pipe");

	pid1 = fork();
	if (pid1 == -1)
		error_exit("fork");
	if (pid1 == 0)
		child_process(argv[2], envp, fd, infile);

	pid2 = fork();
	if (pid2 == -1)
		error_exit("fork");
	if (pid2 == 0)
		parent_process(argv[3], envp, fd, outfile);

	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
