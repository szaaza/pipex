/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 11:28:27 by codespace         #+#    #+#             */
/*   Updated: 2025/10/09 22:01:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define RED "\x1B[31m"

/* Libft functions - names unchanged */
void	*ft_calloc(size_t count, size_t size);
size_t	ft_total_words(char const *str, char c1);
int		search_str(char c, char const *s, char **array);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		free_str2(char **str2, int k1);
void	ft_freestr(char **str1, int i1);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_error(void);

/* Pipex core functions - refactored names */
char	*find_executable_path(char *path_env, char **cmd_args, int index);
void	execute_command(char *command, char **envp, int env_index);
void	execute_first_command(int pipe_fds[], char **argv, char **envp);
void	execute_second_command(int pipe_fds[], char **argv, char **envp);

#endif