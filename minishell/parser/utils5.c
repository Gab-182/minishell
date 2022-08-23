/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 05:19:39 by isaad             #+#    #+#             */
/*   Updated: 2022/08/09 05:19:40 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_flag(t_data *info, int i, char c)
{
	if (c == 39)
		info->flag = 1;
	else
		info->flag = 0;
	i++;
	return (i);
}

int	increment_till_next_quote(t_dquote *data, char *cmd, int i, char c)
{
	while (cmd[i] != c)
	{
		if (cmd[i] == 0)
		{
			data->dquote = 1;
			return (0);
		}
		i++;
	}
	return (i);
}

int	increment_till_next_op(t_data *data, int i)
{
	char	c;

	while ((data->full_cmd[i] != '<' && data->full_cmd[i] != '>')
		&& data->full_cmd[i])
	{
		if ((data->full_cmd[i] == 39 || data->full_cmd[i] == 34))
		{
			c = data->full_cmd[i];
			i++;
			while (data->full_cmd[i] != c && data->full_cmd[i])
				i++;
			i++;
		}
		else
			i++;
	}
	return (i);
}

int	checker(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !cmd[0])
		return (0);
	while (ft_isspace(cmd[i]) && cmd[i])
		i++;
	if (cmd[i] == 0)
		return (0);
	return (1);
}

void	print_error(char *s)
{
	printf("%s\n", s);
	rl_on_new_line();
}
