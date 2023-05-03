/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_w_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:51:15 by mmoramov          #+#    #+#             */
/*   Updated: 2023/05/03 21:53:36 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "libft/libft.h"

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

char ft_set_quote(char actQuote)
{
	char	singlequote;
	char	doublequote;
	char	newQuote;

	singlequote = '\'';
	doublequote = '\"';
	if (actQuote == singlequote)
		newQuote = doublequote;
	else
		newQuote = singlequote;
	return(newQuote);
}

char *ft_substr_wo_escapedchar(char const *s, unsigned int start, size_t len)
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

int	ft_wordlen_w_quotes(char const *s, char c)
{
	int		i;
	char	actQuote;
	int		nestednbr;

	actQuote = '\0';
	nestednbr = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c && actQuote == '\0')
			return(i);
		if (ft_strchr("\'\"", s[i]))
		{
			if(actQuote != '\0' && s[i] == actQuote)
			{
				nestednbr -=1;
				if (nestednbr == 0)
					actQuote = '\0';
				else
					actQuote = ft_set_quote(actQuote);
			}
			else
			{
				actQuote = s[i];
				nestednbr +=1;
			}
		}
		i++;
	}
	return (i);
}

int	ft_wordlen_w_quotes_wo_escapedchar(char const *s, char c)
{
	int		i;
	char	actQuote;
	int		nestednbr;

	actQuote = '\0';
	nestednbr = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c && actQuote == '\0')
			return(i);
		if (ft_strchr("\'\"", s[i]) && (s[i-1] != '\\'))
		{
			if(actQuote != '\0' && s[i] == actQuote)
			{
				nestednbr -=1;
				if (nestednbr == 0)
					actQuote = '\0';
				else
					actQuote = ft_set_quote(actQuote);
			}
			else
			{
				actQuote = s[i];
				nestednbr +=1;
			}
		}
		i++;
	}
	return (i);
}

void	ft_free_w_quotes(char **s, int len)
{
	while (len--)
		free(s[len]);
	free(s);
}

char	**ft_split_w_quotes(char *s, char c)
{
	int		i;
	int		j;
	char	**p;
	int		start;

	i = 0;
	j = 0;
	start = 0;

	p = malloc(sizeof(char *) * (500 + 1));
	if (!p)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			p[j] = ft_substr_wo_escapedchar(s, start, ft_wordlen_w_quotes_wo_escapedchar(&s[i], c));
			if (!p[j])
			{
				ft_free_w_quotes(p, j);
				return (NULL);
			}

			j++;
			i += (ft_wordlen_w_quotes(&s[i], c) - 1);
			start = i+1;
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
	char *s  = "awk \"{count++} END {printf \\\"count:%i\\\" , count}\"";

	 char **t;
	 t = ft_split_w_quotes(s, ' ');

	int i;
	i = 0;
	while (t[i])
    {
		printf("%s\n", t[i]);
		i++;
	}
	//gcc ft_split_w_quotes.c libft/libft.a && ./a.out
}
*/
