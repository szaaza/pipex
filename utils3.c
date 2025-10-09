/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 11:38:01 by codespace         #+#    #+#             */
/*   Updated: 2025/10/09 21:57:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i1;

	i1 = 0;
	while (s[i1] != '\0')
	{
		write(fd, &s[i1], sizeof(char));
		i1++;
	}
	write(fd, "\n", 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i1;

	i1 = 0;
	while (s[i1] != '\0')
	{
		write(fd, &s[i1], sizeof(char));
		i1++;
	}
}

void	ft_error(void)
{
	perror(RED "Error");
	exit(1);
}
