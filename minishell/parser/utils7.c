/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 05:19:49 by isaad             #+#    #+#             */
/*   Updated: 2022/08/15 04:57:45 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*============================================================================*/
int	incrementer(const char *s, int i)
{
	char	c;

	if ((s[i] == 39 || s[i] == 34))
	{
		c = s[i];
		i++;
		while (s[i] != c && s[i])
			i++;
	}
	return (i);
}

/*============================================================================*/
int	hair_extension(int x, t_data *data, int nb_of_op)
{
	int	size_of_full_op;
	int	i;

	i = 0;
	while (x < nb_of_op)
	{
		i = increment_till_next_op(data, i);
		size_of_full_op = check_size_of_full_op(data, i);
		if (size_of_full_op == 0)
			return (0);
		skip_oop(data, &i);
		x++;
	}
	return (1);
}

/*============================================================================*/
int	check_full_op(t_data *data)
{
	int	nb_of_op;
	int	x;
	int	i;
	int	size_of_full_op;

	nb_of_op = count_op(data);
	x = 0;
	i = 0;
	if (!hair_extension(x, data, nb_of_op))
		return (0);
	alloc_op(data, nb_of_op);
	while (x < nb_of_op)
	{
		i = increment_till_next_op(data, i);
		size_of_full_op = 0;
		size_of_full_op = check_size_of_full_op(data, i);
		if (size_of_full_op == 0)
			return (0);
		data->full_op[x] = ft_calloc(sizeof(char), size_of_full_op + 1);
		skip_oop(data, &i);
		x++;
	}
	return (1);
}

/*============================================================================*/
int	check_error_status(int pipe_num, char *cmd_line, t_dquote *for_all)
{
	if (for_all->dquote == 1)
	{
		print_error("error quotes not closed");
		return (0);
	}
	if (count_pipes(cmd_line, pipe_num) == 50505050)
		return (0);
	return (1);
}

/*============================================================================*/