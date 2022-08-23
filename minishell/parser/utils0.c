/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 05:19:11 by isaad             #+#    #+#             */
/*   Updated: 2022/08/18 13:50:12 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	incrementer55(t_data *data, int i)
{
	char	c;

	while ((data->full_cmd[i] != '<' && data->full_cmd[i] != '>')
		&& data->full_cmd[i])
	{
		if ((data->full_cmd[i] == 39 || data->full_cmd[i] == 34))
		{
			c = data->full_cmd[i];
			i++;
			while (data->full_cmd[i] != c)
			{
				i++;
			}
		}
		i++;
	}
	return (i);
}

int	incrementer_3(int x, t_data *data)
{
	char	c;

	if ((data->full_cmd[x] == 39 || data->full_cmd[x] == 34))
	{
		c = data->full_cmd[x];
		x++;
		while (data->full_cmd[x] != c)
		{
			x++;
		}
	}
	return (x);
}

int	error_for_op(t_data *data, int i)
{
	if (data->full_cmd[i] == '<' || data->full_cmd[i] == '>')
	{
		printf("bash: unexpected token `%c'\n", data->full_cmd[i]);
		g_data->return_state = 258;
		rl_on_new_line();
		return (0);
	}
	return (1);
}

int	error_for_size_op(t_data *data, int i)
{
	if (data->full_cmd[i] == '<' || data->full_cmd[i] == '>'
		|| data->full_cmd[i] == 0)
	{
		printf("bash: unexpected token `%c'\n", data->full_cmd[i]);
		g_data->return_state = 258;
		rl_on_new_line();
		return (0);
	}
	return (1);
}

void	skip_oop(t_data *data, int *i)
{
	int		j;

	j = 0;
	while ((data->full_cmd[*i] == '<' || data->full_cmd[*i] == '>')
		&& data->full_cmd[*i] && j < 2)
	{
		(*i)++;
		j++;
	}
	j++;
	while (ft_isspace(data->full_cmd[*i]) && data->full_cmd[*i])
		(*i)++;
	j = size_op_skip(data, i, j);
}
