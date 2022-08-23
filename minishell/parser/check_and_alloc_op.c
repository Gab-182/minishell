/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_alloc_op.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 05:18:06 by isaad             #+#    #+#             */
/*   Updated: 2022/08/09 05:18:08 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	copy_all_op(t_data *data)
{
	int	nb_of_op;
	int	x;
	int	i;
	int	size_of_full_op;

	i = 0;
	nb_of_op = count_op(data);
	x = 0;
	while (x < nb_of_op)
	{
		i = incrementer55(data, i);
		copy_op_line(data, i, x);
		size_of_full_op = check_size_of_full_op(data, i);
		if (size_of_full_op == 0)
			return (0);
		skip_oop(data, &i);
		x++;
	}
	return (0);
}

int	count_op(t_data *data)
{
	int		y;
	int		x;
	int		i;

	y = 0;
	x = 0;
	i = 1;
	while (data->full_cmd[x])
	{
		x = incrementer_3(x, data);
		if ((data->full_cmd[x] == '<' || data->full_cmd[x] == '>') && i)
		{
			i = 0;
			y++;
		}
		else if ((data->full_cmd[x] != '<' && data->full_cmd[x] != '>')
			&& i == 0)
			i = 1;
		x++;
	}
	return (y);
}

void	full_copy(t_data *data, int i, int j, int x)
{
	char	c;

	while (!ft_isspace(data->full_cmd[i]) && (data->full_cmd[i] != '<'
			&& data->full_cmd[i] != '>') && data->full_cmd[i])
	{
		if (data->full_cmd[i] == 39 || data->full_cmd[i] == 34)
		{
			c = data->full_cmd[i];
			i++;
			while (data->full_cmd[i] != c)
			{
				data->full_op[x][j] = data->full_cmd[i];
				j++;
				i++;
			}
			i++;
		}
		else
		{
			data->full_op[x][j] = data->full_cmd[i];
			j++;
			i++;
		}
	}
	data->full_op[x][j] = 0;
}

int	copy_op_line(t_data *data, int i, int x)
{
	int		j;

	j = 0;
	while ((data->full_cmd[i] == '<' || data->full_cmd[i] == '>')
		&& data->full_cmd[i])
	{
		data->full_op[x][j] = data->full_cmd[i];
		i++;
		j++;
	}
	while (ft_isspace(data->full_cmd[i]) && data->full_cmd[i])
		i++;
	data->full_op[x][j] = ' ';
	j++;
	full_copy(data, i, j, x);
	return (0);
}

int	size_op_from_full(t_data *data, int i, int j)
{
	char	c;

	while ((!ft_isspace(data->full_cmd[i])) && data->full_cmd[i]
		&& (data->full_cmd[i] != '<' && data->full_cmd[i] != '>'))
	{
		if (!error_for_op(data, i))
			return (0);
		else if (data->full_cmd[i] == 39 || data->full_cmd[i] == 34)
		{
			c = data->full_cmd[i];
			i++;
			while (data->full_cmd[i] != c && data->full_cmd[i])
			{
				j++;
				i++;
			}
			i++;
		}
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}
