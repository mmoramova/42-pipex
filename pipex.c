/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:17:53 by mmoramov          #+#    #+#             */
/*   Updated: 2023/06/18 12:07:59 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_child_process(char **argv, char **env, int *fd)
{
	int	file;

	file = open(argv[1], O_RDONLY, 0666);
	if (file == -1)
		ft_exits(errno, argv[1], strerror(errno));
	dup2(fd[1], STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
	ft_close(fd, file);
	ft_execve_prepare(argv[2], env);
	return (0);
}

int	ft_parent_process(char **argv, char **env, int *fd)
{
	int	file;

	file = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (file == -1)
		ft_exit(1);
	dup2(fd[0], STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	ft_close(fd, file);
	ft_execve_prepare(argv[3], env);
	return (0);
}

int	main(int argc, char **argv, char *env[])
{
	int	fd[2];
	int	pid;

	if (argc != 5)
		ft_exits(1, "Please input 5 arguments", NULL);
		//ft_exit(1); //error
	if (pipe(fd) == -1)
		ft_exits(errno, strerror(errno), NULL);
	pid = fork();
	if (pid == -1)
		ft_exits(errno, strerror(errno), NULL);
	if (pid == 0)
		ft_child_process(argv, env, fd);
	else
		ft_parent_process(argv, env, fd);
	waitpid(pid, NULL, 0);
	return (0);
}
