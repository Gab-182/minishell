/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_and_split_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 05:18:25 by isaad             #+#    #+#             */
/*   Updated: 2022/08/16 03:16:33 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*============================================================================*/

int	skip_op(t_data *data, int i)
{
	int		j;

	j = 0;
	while ((data->full_cmd[i] == '>' || data->full_cmd[i] == '<')
		&& data->full_cmd[i])
	{
		i++;
		j++;
	}
	while (ft_isspace(data->full_cmd[i]) && data->full_cmd[i])
	{
		i++;
		j++;
	}
	while (!ft_isspace(data->full_cmd[i]) && data->full_cmd[i])
	{
		j = increment_j(data, i, j);
		i = increment_i(data, i);
	}
	return (j);
}

/*============================================================================*/

int	skip_i(t_data *data, int i)
{
	int		x;
	char	c;

	if (data->full_cmd[i] == '>' || data->full_cmd[i] == '<')
	{
		x = skip_op(data, i);
		i += x;
	}
	else if ((data->full_cmd[i] == 39 || data->full_cmd[i] == 34))
	{
		c = data->full_cmd[i];
		i++;
		while (data->full_cmd[i] != c)
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

int	copy_only_cmd(t_data *data)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	c = 0;
	while (data->full_cmd[i])
	{
		j = skip_j(data, i, j, c);
		i = skip_i(data, i);
	}
	if (j == 0)
		return (0);
	data->cmd = ft_calloc(sizeof(char), j + 1);
	start_copy_cmd(data);
	return (1);
}

/*============================================================================*/

int	i_hate_norm(t_data *data, int i, int j, int x)
{
	while (data->full_cmd[i])
	{
		if (data->full_cmd[i] == '>' || data->full_cmd[i] == '<')
		{
			x = skip_op(data, i);
			i += x;
		}
		else if ((data->full_cmd[i] == 39 || data->full_cmd[i] == 34))
		{
			j = incrementjj(data, i, j);
			i = incrementii(data, i);
		}
		else
		{
			data->cmd[j] = data->full_cmd[i];
			i++;
			j++;
		}
	}
	return (j);
}

/*============================================================================*/
void	start_copy_cmd(t_data *data)
{
	int		i;
	int		j;
	int		x;

	i = 0;
	j = 0;
	x = 0;
	j = i_hate_norm(data, i, j, x);
	data->cmd[j] = '\0';
	if (data->cmd[0])
		data->s_cmd = ft_split_og(data->cmd, ' ');
}

/*============================================================================*/
