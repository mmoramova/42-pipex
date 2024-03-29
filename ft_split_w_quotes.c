/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_w_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:51:15 by mmoramov          #+#    #+#             */
/*   Updated: 2023/06/18 17:01:23 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_wordcount_w_quotes(char const *s, char c)
{
	int	nbr;
	int	is_c;

	nbr = 0;
	is_c = 1;
	while (*s)
	{
		if (*s != c && is_c)
		{
			is_c = 0;
			nbr++;
		}
		else if (*s == c)
			is_c = 1;
		s++;
	}
	return (nbr);
}

char	*ft_substr_woechar(char const *s, unsigned int start, size_t len)
{
	unsigned int	len_s;
	unsigned int	i;
	unsigned int	j;
	char			*p;

	len_s = ft_strlen(s);
	i = 0;
	j = 0;
	if (len_s <= start)
		len = 0;
	else if (len_s < start + len)
		len = len_s - start;
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (s[i] && len--)
	{
		if (s[start + i + j] == '\\')
			j += 1;
		p[i] = s[start + i + j];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	**ft_free_w_quotes(char **s, int len)
{
	while (len--)
		free(s[len]);
	free(s);
	return (NULL);
}

char	**ft_split_w_quotes(char *s, char c, int start)
{
	int		i;
	int		j;
	char	**p;

	(0 || (i = 0) || (j = 0));
	p = malloc(sizeof(char *) * (100 + 1));
	if (!p)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			p[j] = ft_substr_woechar(s, start, ft_wordlen_wq_woechar(&s[i], c));
			if (!p[j])
				return (ft_free_w_quotes(p, j));
			j++;
			i += (ft_wordlen_w_quotes(&s[i], c) - 1);
			start = i + 1;
		}
		else if (s[i] == c)
			start++;
		i++;
	}
	p[j] = NULL;
	return (p);
}

/*
int main(void)
{
	char *s  = "awk \"{count++} END {printf \\\"count:%ix\\\" , count}\"";

	 char **t;
	 t = ft_split_w_quotes(s, ' ');

	int i;
	i = 0;
	while (t[i])
    {
		printf("%s\n", t[i]);
		i++;
	}
	printf("%s\n", t[2]);
	//gcc ft_split_w_quotes.c libft/libft.a && ./a.out
}
*/
