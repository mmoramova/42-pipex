/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:22:33 by mmoramov          #+#    #+#             */
/*   Updated: 2023/05/01 19:18:29 by mmoramov         ###   ########.fr       */
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
        exit(1);
    }
    dup2(fd[0], STDIN_FILENO);
    dup2(file, STDOUT_FILENO);

    close(fd[0]);
    close(fd[1]);
    close(file);

    command = ft_split_w_quotes(argv[3], ' ');

	int j;
	j = 0;

	//ft_putstr_fd(command[0], 2);
	//ft_putstr_fd(command[1], 2);
	//ft_putstr_fd("\n", 2);

	while (command[j])
	{
		command[j] = ft_strtrim(command[j], "\"\'");
		j++;
	}

	//ft_putstr_fd(command[0], 2);
	//ft_putstr_fd(command[1], 2);
	//ft_putstr_fd("\n", 2);

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

    while (env[i] && ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	if (env[i])
		paths = ft_split(env[i] + 5, ':');
	else
		paths = ft_split("/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin", ':');

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
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(command[0], 2);
 	ft_putstr_fd(": command not found\n", 2);
   	exit(127);

    //execvp("ping", ping);
    //execlp("ping", "ping", "-c", "5", "google.com", NULL);  //ends by itself
    return(0);
}
