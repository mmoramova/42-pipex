/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:17:53 by mmoramov          #+#    #+#             */
/*   Updated: 2023/02/12 18:45:36 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

/*int child_process()
{
    TODO
    return(0);
}

int parent_process()
{
    TODO
    return(0);
}*/

int main(int argc, char **argv, char *env[])
{
    int fd[2];
    int pid;
    int i;
    char **paths;
    char *path;
    char **command1;
    char **command2;
    int file1;
    int file2;
    
    i = 0;
     if (argc != 5)
       return 1; //error
       
    command1 = ft_split(argv[2], ' ');
    command2 = ft_split(argv[3], ' ');

    while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
    paths = ft_split(env[i] + 5, ':');

    /*int j = 0;
    while (paths[j])
    {
        printf("%s \n", paths[j]);
        j++;
    }*/

    file1 = open(argv[1], O_RDONLY, 0777);
    file2 = open(argv[4], O_WRONLY | O_CREAT, 0777);
   
    pipe(fd);
    pid = fork();

    if (pid == 0) //child process -execute ping
    {
        dup2(file1, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        
        close(fd[0]);
        close(fd[1]);
        close(file1);
        close(file2);
           
        i = 0;
        while (paths[i])
        {
            path = ft_strjoin(paths[i], "/");
		    path = ft_strjoin(path, command1[0]);
		
            if (access(path, F_OK) == 0)
                execve(path, command1, env);
            i++;
        }
        //execvp("ping", ping);
        //execlp("ping", "ping", "-c", "5", "google.com", NULL);  //ends by itself
    }

    else //parent process -execute grep
    {
        dup2(fd[0], STDIN_FILENO);
        dup2(file2, STDOUT_FILENO);
        
        close(fd[0]);
        close(fd[1]);
        close(file1);
        close(file2);

        i = 0;
        while (paths[i])
        {
            path = ft_strjoin(paths[i], "/");
		    path = ft_strjoin(path, command2[0]);
		
            if (access(path, F_OK) == 0)
                execve(path, command2, env);
            i++;
        }
        //execlp("grep", "grep", "round", NULL);  //ends by itself
     }

        //close(fd[0]);
        //close(fd[1]);
        
        waitpid(pid, NULL, 0);
    //|
    return (0);

    //pipex ping.txt "ping -c 5 google.com" "wc -l" textout
}