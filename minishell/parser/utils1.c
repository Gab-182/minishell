/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 05:19:18 by isaad             #+#    #+#             */
/*   Updated: 2022/08/09 05:19:19 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_size_of_full_op(t_data *data, int i)
{
	int		j;

	j = 0;
	while ((data->full_cmd[i] == '<' || data->full_cmd[i] == '>')
		&& data->full_cmd[i] && j < 2)
	{
		if ((data->full_cmd[i] == '>' && data->full_cmd[i + 1] == '<'))
		{
			printf("bash: unexpected token `%c'\n", data->full_cmd[i + 1]);
			rl_on_new_line();
			return (0);
		}
		i++;
		j++;
	}
	j++;
	while (ft_isspace(data->full_cmd[i]) && data->full_cmd[i])
		i++;
	if (!error_for_size_op(data, i))
		return (0);
	j = size_op_from_full(data, i, j);
	return (j);
}

int	size_op_skip(t_data *data, int *i, int j)
{
	char	c;

	while ((!ft_isspace(data->full_cmd[*i])) && data->full_cmd[*i]
		&& (data->full_cmd[*i] != '<' && data->full_cmd[*i] != '>'))
	{
		if (!error_for_op(data, *i))
			return (0);
		else if (data->full_cmd[*i] == 39 || data->full_cmd[*i] == 34)
		{
			c = data->full_cmd[*i];
			(*i)++;
			while (data->full_cmd[*i] != c && data->full_cmd[*i])
			{
				j++;
				(*i)++;
			}
			(*i)++;
		}
		else
		{
			(*i)++;
			j++;
		}
	}
	return (j);
}

int	increment_i(t_data *data, int i)
{
	char	c;

	if (data->full_cmd[i] == 39 || data->full_cmd[i] == 34)
	{
		c = data->full_cmd[i];
		i++;
		while (data->full_cmd[i] != c && data->full_cmd[i])
		{
			i++;
		}
		i++;
	}
	else
	{
		i++;
	}
	return (i);
}

int	increment_j(t_data *data, int i, int j)
{
	char	c;

	if (data->full_cmd[i] == 39 || data->full_cmd[i] == 34)
	{
		c = data->full_cmd[i];
		i++;
		j++;
		while (data->full_cmd[i] != c && data->full_cmd[i])
		{
			i++;
			j++;
		}
		i++;
		j++;
	}
	else
	{
		i++;
		j++;
	}
	return (j);
}

int	skip_j(t_data *data, int i, int j, char c)
{
	int	x;

	x = 0;
	if (data->full_cmd[i] == '>' || data->full_cmd[i] == '<')
	{
		x = skip_op(data, i);
		i += x;
	}
	else if ((data->full_cmd[i] == 39 || data->full_cmd[i] == 34))
	{
		c = data->full_cmd[i++];
		j++;
		while (data->full_cmd[i++] != c)
			j++;
		i++;
		j++;
	}
	else
	{
		i++;
		j++;
	}
	return (j);
}
