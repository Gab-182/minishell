/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 05:19:22 by isaad             #+#    #+#             */
/*   Updated: 2022/08/09 05:19:23 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	incrementii(t_data *data, int i)
{
	char	c;

	c = data->full_cmd[i];
	i++;
	while (data->full_cmd[i] != c)
		i++;
	i++;
	return (i);
}

int	incrementjj(t_data *data, int i, int j)
{
	char	c;

	c = data->full_cmd[i];
	data->cmd[j] = data->full_cmd[i];
	j++;
	i++;
	while (data->full_cmd[i] != c)
	{
		data->cmd[j] = data->full_cmd[i];
		j++;
		i++;
	}
	data->cmd[j] = data->full_cmd[i];
	j++;
	i++;
	return (j);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_strlen_n(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	isenv_se(char c)
{
	if (c == '#' || c == '$' || c == '&' || c == '-' || c == '@' || c
		== '!' || c == '*')
		return (1);
	return (0);
}
