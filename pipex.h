/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:17:56 by mmoramov          #+#    #+#             */
/*   Updated: 2023/05/01 18:04:34 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include "libft/libft.h"

int ft_child_process(char **argv, char **env, int *fd);
int ft_parent_process(char **argv, char **env, int *fd);
char	**ft_split_w_quotes(char *s, char c);
#endif
