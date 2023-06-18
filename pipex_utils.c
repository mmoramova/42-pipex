/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:46:07 by mmoramov          #+#    #+#             */
/*   Updated: 2023/06/18 17:55:30 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close(int fd[2], int file)
{
	close(fd[0]);
	close(fd[1]);
	if (file > 0)
		close(file);
}

void	ft_exit(int exitnumber, char *txt, char *txt2)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(txt, 2);
	if (txt2 && ft_strlen(txt2) > 0)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(txt2, 2);
	}
	ft_putstr_fd("\n", 2);
	exit(exitnumber);
}

char	**ft_get_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	if (env[i])
		paths = ft_split(env[i] + 5, ':');
	else
		paths = ft_split(DEF_PATH, ':');
	return (paths);
}

void	ft_execve(char *path, char **command, char **env)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) != 0)
			ft_exit(126, command[0], strerror(errno));
		if (execve(path, command, env) == -1)
			ft_exit(errno, strerror(errno), NULL);
	}
}

void	ft_execve_prepare(char *argv, char **env)
{
	char	**command;
	int		i;
	int		j;
	char	**paths;

	j = 0;
	i = 0;
	command = ft_split_w_quotes(argv, ' ', 0);
	if (argv[0] == '.' && argv[1] == '/' && ft_strchr(argv, 32))
		ft_exit(127, command[0], "No such file or directory");
	while (command[j])
	{
		if (command[j][0] == '\'')
			command[j] = ft_strtrim(command[j], "\'");
		else if (command[j][0] == '\"')
			command[j] = ft_strtrim(command[j], "\"");
		j++;
	}
	if (ft_strchr(command[0], '/'))
		ft_execve(command[0], command, env);
	paths = ft_get_paths(env);
	while (paths[i])
		ft_execve(ft_strjoin(ft_strjoin(paths[i++], "/"),
				command[0]), command, env);
	ft_exit(127, command[0], "command not found");
}
