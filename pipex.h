/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 11:28:27 by codespace         #+#    #+#             */
/*   Updated: 2025/10/04 11:28:37 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

void	error_exit(const char *msg);
char	**get_path(char **envp);
char	*find_command(char *cmd, char **paths);
void	child_process(char *cmd, char **envp, int *pipefd, int infile);
void	parent_process(char *cmd, char **envp, int *pipefd, int outfile);

#endif
