/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:22:33 by mmoramov          #+#    #+#             */
/*   Updated: 2023/04/29 20:36:14 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "pipex.h"

int ft_parent_process(char **argv, char **env, int *fd)
{
    int     file;
    char    **command;
    int     i;
    char    **paths;
    char    *path;

    i = 0;

    file = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0666);
    if (file == -1)
    {
        //ft_putstr_fd(strerror(errno), 2);;
        exit(21);
    }
    dup2(fd[0], STDIN_FILENO);
    dup2(file, STDOUT_FILENO);

    close(fd[0]);
    close(fd[1]);
    close(file);

    command = ft_split(argv[3], ' ');
    //command = ft_split("wc -l", ' ');
	if (ft_strchr(command[0], '/')) //&& ft_strnstr(argv[2],".sh",100))
    {
        path = command[0];
		//ft_putstr_fd(path, 2);
		//ft_putstr_fd("\n", 2);
        if (access(path, F_OK) == 0  && access(path, X_OK) == 0)
        {
            if (execve(path, command, env) == -1)
            {
                //ft_putstr_fd(strerror(errno), 2);
                exit(22);
            }
        }
    }

    while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
    paths = ft_split(env[i] + 5, ':');

    i = 0;
    while (paths[i])
    {
        path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, command[0]);
		//ft_putstr_fd(path, 2);
		//ft_putstr_fd("\n", 2);
        if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
        {
            //ft_putstr_fd(path, 2);
			//ft_putnbr_fd(execve(path, command, env), 2);
			if (execve(path, command, env) == -1)
            {
                //ft_putstr_fd(strerror(errno), 2);
                exit(23);
            }
        }
        i++;
    }
 	ft_putstr_fd("pipexPP: input: command not found\n", 2);
   	exit(127);

    //execvp("ping", ping);
    //execlp("ping", "ping", "-c", "5", "google.com", NULL);  //ends by itself
    return(0);
}
