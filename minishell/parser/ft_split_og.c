/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_og.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 08:19:12 by isaad             #+#    #+#             */
/*   Updated: 2022/08/19 19:00:18 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wordscount_og(char const *s, char c)
{
	int		i;
	int		words;
	int		flag;

	i = 0;
	words = 0;
	flag = 1;
	while (s[i])
	{
		i = incrementer(s, i);
		if (s[i] == c && !flag)
			flag = 1;
		else if (s[i] != c && flag)
		{
			words++;
			flag = 0;
		}
		i++;
	}
	return (words);
}

char	*wordscut_og(char const *s, int len, int start)
{
	char	*c;
	int		i;

	i = 0;
	c = (char *)malloc(len + 1);
	if (!c)
		return (0);
	while (len > 0)
	{
		c[i++] = s[start - len];
		len--;
	}
	c[i] = '\0';
	return (c);
}

int	incrementer_2(const char *s, int i, char c)
{
	char	cc;
	int		strl;

	strl = 0;
	while (s[i] != c && s[i])
	{
		if ((s[i] == 39 || s[i] == 34))
		{
			cc = s[i];
			strl++;
			i++;
			while (s[i] != cc && s[i])
			{
				i++;
				strl++;
			}
		}
		if (i++ >= 0)
			strl++;
	}
	return (strl);
}

void	wordsplit_og(char **strs, char c, char const *s, int words)
{
	int		i;
	int		strl;
	int		word;

	i = 0;
	word = 0;
	strl = 0;
	while (word < words)
	{
		while (s[i] && s[i] == c)
			++i;
		strl = incrementer_2(s, i, c);
		i += strl;
		strs[word++] = wordscut_og(s, strl, i);
		strl = 0;
	}
	strs[word] = 0;
}

/*============================================================================*/
char	**ft_split_og(char const *s, char c)
{
	char	**a;
	int		words;

	if (!s)
		return (0);
	words = wordscount_og(s, c);
	a = (char **)malloc((words + 1) * sizeof(char *));
	if (!a)
		return (0);
	wordsplit_og(a, c, s, words);
	return (a);
}

/*============================================================================*/