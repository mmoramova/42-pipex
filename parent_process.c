/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:22:33 by mmoramov          #+#    #+#             */
/*   Updated: 2023/06/12 19:31:42 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "pipex.h"

int ft_parent_process(char **argv, char **env, int *fd)
{
	int		file;
	char	**command;
	int		i;
	int 	j;
	char	**paths;
	char	*path;

	j = 0;
	i = 0;

	file = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (file == -1)
		exit(1);

	dup2(fd[0], STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(file);


	command = ft_split_w_quotes(argv[3], ' ');

	while (command[j])
	{
		if (command[j][0] == '\'')
			command[j] = ft_strtrim(command[j], "\'");
		else if (command[j][0] == '\"')
			command[j] = ft_strtrim(command[j], "\"");
		j++;
	}

	if (ft_strchr(command[0], '/'))
	{
		path = command[0];
			if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) != 0)
				exit(126);
			if (execve(path, command, env) == -1)
				exit(22);
		}
	}

	while (env[i] && ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	if (env[i])
		paths = ft_split(env[i] + 5, ':');
	else
		paths = ft_split(DEF_PATH, ':');

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, command[0]);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) != 0)
				exit(126);
			if (execve(path, command, env) == -1)
			{
				exit(23);
			}
		}
		i++;
	}
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(command[0], 2);
 	ft_putstr_fd(": command not found\n", 2);
	exit(127);

	return(0);
}
