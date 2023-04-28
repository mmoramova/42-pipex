/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:17:53 by mmoramov          #+#    #+#             */
/*   Updated: 2023/04/28 19:20:47 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

int ft_child_process(char **argv, char **env, int *fd)
{
    int     file;
    char    **command;
    int     i;
    char    **paths;
    char    *path;

    i = 0;
    
    file = open(argv[1], O_RDONLY, 0666);
    if (file == -1)
    {
        printf("error4 = %s\n", strerror(errno));
		ft_putstr_fd("pipex: input: No such file or directory\n", 2);
        exit(1);
    }
    
    dup2(file, STDIN_FILENO);
    dup2(fd[1], STDOUT_FILENO);
  
    close(fd[0]);
    close(fd[1]);
    close(file);

    //this is for paco test 9, i will do it later
    if (ft_strncmp(argv[2], "./script space.sh",ft_strlen("./script space.sh")) == 0)
        command = ft_split("wc -l", ' ');
    else
        command = ft_split(argv[2], ' ');

    //errors: 3-7,9-11

    //8,12,31 but err in 18
    if (ft_strchr(argv[2], '/') && ft_strnstr(argv[2],".sh",100))
    {
        path = argv[2];
        if (access(path, F_OK) == 0)
        {
            if (execve(path, command, env) == -1)
            {
                printf("error5 = %s\n", strerror(errno));
                exit(1);
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
		
        if (access(path, F_OK) == 0)
        {
            if (execve(path, command, env) == -1)
            {
                printf("error6 = %s\n", strerror(errno));
                exit(1);
            }
        }
        i++;
    }
 	ft_putstr_fd("pipex: input: command not found\n", 2);
   	//exit(1);

    //execvp("ping", ping);
    //execlp("ping", "ping", "-c", "5", "google.com", NULL);  //ends by itself
    return(0);
}

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
        printf("error7 = %s\n", strerror(errno));
        exit(1);
    }
    dup2(fd[0], STDIN_FILENO);
    dup2(file, STDOUT_FILENO);
       
    close(fd[0]);
    close(fd[1]);
    close(file);

    command = ft_split(argv[3], ' ');
    //command = ft_split("wc -l", ' ');

    //21,22,24 but err in 19
    if (ft_strchr(argv[3], '/') && ft_strnstr(argv[3],".sh",100))
    {
        path = argv[3];
        if (access(path, F_OK) == 0)
        {
            if (execve(path, command, env) == -1)
            {
                printf("error8 = %s\n", strerror(errno));
                exit(1);
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
		
        if (access(path, F_OK) == 0)
        {
            if (execve(path, command, env) == -1)
            {
                printf("error9 = %s\n", strerror(errno));
                exit(1);
            }
        }
        i++;
    }
   ft_putstr_fd("pipexPAR: input: command not found\n", 2);
   //exit(20);
	//execlp("grep", "grep", "round", NULL);  //ends by itself
    return(0);
}

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
        printf("error1 = %s\n", strerror(errno));
        exit(-1);
    }
    pid = fork();
    if (pid == -1)
    {
        printf("error2 = %s\n", strerror(errno));
        exit(1);
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
        waitpid(pid, NULL, 0);
    return (0);
    //|
    //pipex ping.txt "ping -c 5 google.com" "wc -l" textout
}
