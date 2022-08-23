/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 10:53:53 by gabdoush          #+#    #+#             */
/*   Updated: 2022/07/02 17:34:12 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	sup_str_len(char const *s, char c);
static size_t	count_sup_str(char const *s, char c);	

/*============================================================================*/
char	**ft_split(char const *s, char c)
{
	char	**full_str;
	size_t	sup_str_number;
	size_t	n;

	n = 0;
	if (!s)
		return (NULL);
	sup_str_number = count_sup_str(s, c);
	full_str = (char **)malloc(sizeof(*full_str) * (count_sup_str(s, c) + 1));
	if (!full_str)
		return (NULL);
	while (sup_str_number)
	{
		while (*s == c && *s != '\0')
			s++;
		full_str[n] = ft_substr(s, 0, sup_str_len(s, c));
		if (full_str[n] == NULL)
			return (NULL);
		s = s + sup_str_len(s, c);
		n++;
		sup_str_number--;
	}
	full_str[n] = NULL;
	return (full_str);
}

/*============================================================================*/
static size_t	count_sup_str(char const *s, char c)
{
	size_t		sub_str_num;
	size_t		is_char_c;

	is_char_c = 0;
	sub_str_num = 0;
	while (*s != '\0')
	{
		if (is_char_c == 1 && *s == c)
			is_char_c = 0;
		if (is_char_c == 0 && *s != c)
		{
			is_char_c = 1;
			sub_str_num++;
		}
		s++;
	}
	return (sub_str_num);
}

/*============================================================================*/
static size_t	sup_str_len(const char *s, char c)
{
	size_t		len;

	len = 0;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	return (len);
}

/*============================================================================*/