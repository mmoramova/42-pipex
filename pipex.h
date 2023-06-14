/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:17:56 by mmoramov          #+#    #+#             */
/*   Updated: 2023/06/14 21:47:33 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include "libft/libft.h"

# define DEF_PATH "/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin"

int		ft_child_process(char *argv, char **env, int *fd, int file1);
int		ft_parent_process(char *argv, char **env, int *fd, int file1);
char	**ft_get_paths(char **env);
int		ft_execve(char *path, char **command,char **env);
void	ft_execve_prepare(char *argv, char **env);
char	**ft_split_w_quotes(char *s, char c);
void	ft_exit(int exitnumber);
void	ft_close(int fd[2], int file);
#endif
