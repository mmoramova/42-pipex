/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:17:53 by mmoramov          #+#    #+#             */
/*   Updated: 2023/04/29 20:32:04 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

int main(int argc, char **argv, char *env[])
{
    int fd[2];
    int pid;
    //int fileerr;

    if (argc != 5)
        return 1; //error


    /*fileerr = open("error.log", O_WRONLY | O_TRUNC | O_CREAT, 0777);
    if (fileerr == -1)
    {
        printf("error = %s\n", strerror(errno));
        exit(1);
    }
    dup2(fileerr, STDERR_FILENO);
    close(fileerr);
	*/

    if(pipe(fd) == -1)
    {
        ft_putstr_fd(strerror(errno), 2);
        exit(50);
    }
    pid = fork();
    if (pid == -1)
    {
        ft_putstr_fd(strerror(errno), 2);
        exit(60);
    }

    if (pid == 0) //child process -execute ping
    {
        ft_child_process(argv, env, fd);
    }
    else //parent process -execute grep
    {
        ft_parent_process(argv, env, fd);
    }
		//close(fd[0]);
        //close(fd[1]);
		//exit(70);
        waitpid(pid, NULL, 0);
    return (0);
    //|
    //pipex ping.txt "ping -c 5 google.com" "wc -l" textout
}
