/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 08:19:12 by isaad             #+#    #+#             */
/*   Updated: 2022/08/19 20:31:01 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	alloc_op(t_data *data, int nb_of_op)
{
	data->full_op = malloc((nb_of_op + 1) * sizeof(char *));
	data->operator = malloc((nb_of_op + 1) * sizeof(char *));
	data->file_name = malloc((nb_of_op + 1) * sizeof(char *));
	data->full_op[nb_of_op] = NULL;
	data->operator[nb_of_op] = NULL;
	data->file_name[nb_of_op] = NULL;
}

int	wordscount(char const *s, char c)
{
	int	i;
	int	words;
	int	flag;

	i = 0;
	words = 0;
	flag = 1;
	while (s[i])
	{
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

char	*wordscut(char const *s, int len, int start)
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

void	wordsplit(char **strs, char c, char const *s, int words)
{
	int	i;
	int	strl;
	int	word;

	i = 0;
	word = 0;
	strl = 0;
	while (word < words)
	{
		while (s[i] && s[i] == c)
			++i;
		while (s[i] != c && s[i])
			if (i++ >= 0)
				strl++;
		strs[word++] = wordscut(s, strl, i);
		strl = 0;
	}
	strs[word] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**a;
	int		words;

	if (!s)
		return (0);
	words = wordscount(s, c);
	a = (char **)malloc((words + 1) * sizeof(char *));
	if (!a)
		return (0);
	wordsplit(a, c, s, words);
	return (a);
}
