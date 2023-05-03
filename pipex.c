/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:17:53 by mmoramov          #+#    #+#             */
/*   Updated: 2023/05/03 22:35:18 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

int	main(int argc, char **argv, char *env[])
{
	int fd[2];
	int pid;
	//int fileerr;

	if (argc != 5)
		exit(1); //error

	if(pipe(fd) == -1)
		exit(errno);
	pid = fork();
	if (pid == -1)
		exit(errno);
	if (pid == 0) //child process
		ft_child_process(argv, env, fd);
    else //parent process
		ft_parent_process(argv, env, fd);
		//close(fd[0]);
		//close(fd[1]);
	waitpid(pid, NULL, 0);
	return (0);
	//|
	//./pipex ping.txt "ping -c 5 google.com" "wc -l" textout
}
