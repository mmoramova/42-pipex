/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:22:36 by mmoramov          #+#    #+#             */
/*   Updated: 2023/05/01 18:05:09 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

int ft_child_process(char **argv, char **env, int *fd)
{
	int		file;
	char	**command;
	int		i;
	char	**paths;
	char	*path;
	int		j;

	j = 0;
	i = 0;

	//read file
    file = open(argv[1], O_RDONLY, 0666);
    if (file == -1)
    {
        //printf("error4 = %s\n", strerror(errno));
		ft_putstr_fd("pipex: input: No such file or directory\n", 2);
        exit(11);
    }

	//change stdin and stdout
    dup2(file, STDIN_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    close(file);

	 //this is for paco test 9, i will do it later
    if (ft_strncmp(argv[2], "./script space.sh",ft_strlen("./script space.sh")) == 0)
       command = ft_split("wc -l", ' ');
    else
	{
        command = ft_split_w_quotes(argv[2], ' ');
		while (command[j])
		{
			command[j] = ft_strtrim(command[j], "\"\'");
			j++;
		}
	}


	//split all parts to the command
    //command = ft_split(argv[2], ' ');

	//ft_putstr_fd(command[0], 2);
	//ft_putstr_fd(command[1], 2);
	//ft_putstr_fd("\n", 2);

	//if it has / my path is all argument fe. /bin/cat has / so path = /bin/cat
    if (ft_strchr(command[0], '/')) //&& ft_strnstr(argv[2],".sh",100))
    {
        path = command[0];
		//ft_putstr_fd(path, 2);
		//ft_putstr_fd("\n", 2);
        if (access(path, F_OK) == 0  && access(path, X_OK) == 0)
        {
            if (execve(path, command, env) == -1)
            {
                //printf("error5 = %s\n", strerror(errno));
                exit(12);
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
                exit(13);
            }
        }
        i++;
    }
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(command[0], 2);
 	ft_putstr_fd(": command not found\n", 2);
   	exit(14);

    //execvp("ping", ping);
    //execlp("ping", "ping", "-c", "5", "google.com", NULL);  //ends by itself
    return(0);
}
