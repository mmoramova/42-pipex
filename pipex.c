/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:17:53 by mmoramov          #+#    #+#             */
/*   Updated: 2023/06/14 21:46:33 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	ft_child_process(char *argv, char **env, int *fd, int file)
{
	dup2(fd[1], STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
	ft_close(fd, file);
	ft_execve_prepare(argv, env);
	return(0);
}

int ft_parent_process(char *argv, char **env, int *fd, int file)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	ft_close(fd, file);
	ft_execve_prepare(argv, env);
	return(0);
}

int	main(int argc, char **argv, char *env[])
{
	int	fd[2];
	int	pid;
	int fileIn;
	int fileOut;

	if (argc != 5)
		ft_exit(1); //error
	if (pipe(fd) == -1)
		ft_exit(errno);
	pid = fork();
	if (pid == -1)
		ft_exit(errno);
	if (pid == 0)
	{
		fileIn = open(argv[1], O_RDONLY, 0666);
		if (fileIn == -1)
		{
			ft_putstr_fd("pipex: input: No such file or directory\n", 2);
			ft_exit(11);
		}
		ft_child_process(argv[2], env, fd, fileIn);
	}
	else
	{
		fileOut = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (fileOut == -1)
			ft_exit(1);
		ft_parent_process(argv[3], env, fd, fileOut);
	}
	waitpid(pid, NULL, 0);
	return (0);
}
