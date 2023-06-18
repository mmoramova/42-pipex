/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:38:20 by mmoramov          #+#    #+#             */
/*   Updated: 2023/06/18 17:46:38 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	ft_set_quote(char act_quote, int nestednbr)
{
	char	singlequote;
	char	doublequote;
	char	new_quote;

	if (nestednbr == 0)
		return ('\0');
	singlequote = '\'';
	doublequote = '\"';
	if (act_quote == singlequote)
		new_quote = doublequote;
	else
		new_quote = singlequote;
	return (new_quote);
}

int	ft_wordlen_w_quotes(char const *s, char c)
{
	int		i;
	char	act_quote;
	int		nestednbr;

	act_quote = '\0';
	nestednbr = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c && act_quote == '\0')
			return (i);
		if (ft_strchr("\'\"", s[i]))
		{
			if (act_quote != '\0' && s[i] == act_quote)
				act_quote = ft_set_quote(act_quote, nestednbr);
			else
			{
				act_quote = s[i];
				nestednbr += 1;
			}
		}
		i++;
	}
	return (i);
}

int	ft_wordlen_wq_woechar(char const *s, char c)
{
	int		i;
	char	act_quote;
	int		nestednbr;

	act_quote = '\0';
	nestednbr = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c && act_quote == '\0')
			return (i);
		if (ft_strchr("\'\"", s[i]) && (s[i - 1] != '\\'))
		{
			if (act_quote != '\0' && s[i] == act_quote)
				act_quote = ft_set_quote(act_quote, nestednbr);
			else
			{
				act_quote = s[i];
				nestednbr += 1;
			}
		}
		i++;
	}
	return (i);
}
