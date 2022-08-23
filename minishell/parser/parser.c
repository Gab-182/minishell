/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 05:19:02 by isaad             #+#    #+#             */
/*   Updated: 2022/08/19 20:38:17 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*============================================================================*/
int	count_pipes(char *cmd_line, int j)
{
	int		i;
	char	c;

	i = 0;
	while (cmd_line[i])
	{
		if ((cmd_line[i] == 39 || cmd_line[i] == 34))
		{
			c = cmd_line[i];
			i++;
			while (cmd_line[i] != c && cmd_line[i])
				i++;
		}
		if ((cmd_line[i] == '|' && cmd_line[i + 1] == '|')
			|| (cmd_line[i] == '|' && cmd_line[i + 1] == 0))
		{
			print_error("bash: syntax error near unexpected token `|'");
			return (50505050);
		}
		if (cmd_line[i] == '|')
			j++;
		i++;
	}
	return (j);
}

/*============================================================================*/

int	redirect_all_commands_2(t_data *data)
{
	int	x;
	int	flag;

	x = 0;
	flag = check_full_op(data);
	if (flag == 0)
	{
		data->full_op = NULL;
		data->operator = NULL;
		data->file_name = NULL;
		return (0);
	}
	copy_all_op(data);
	copy_details(data);
	while (data->full_op[x])
	{
		free(data->full_op[x]);
		x++;
	}
	free(data->full_op);
	return (1);
}

/*============================================================================*/
int	redirect_all_commands_1(t_data *data, t_dquote *for_all)
{
	int	x;
	int	y;

	if (!redirect_all_commands_2(data))
		return (0);
	x = 0;
	if (copy_only_cmd(data))
	{
		x = 0;
		y = wordscount_og(data->cmd, ' ');
		free(data->cmd);
		while (x < y)
		{
			data->s_cmd[x] = check_expand(data->s_cmd[x], data);
			data->s_cmd[x] = check_dquote
				(data->s_cmd[x], for_all, data);
			x++;
		}
	}
	return (1);
}

/*============================================================================*/
int	redirect_all_commands(t_data *data, t_dquote *for_all)
{
	if (data->full_cmd)
	{
		if (!redirect_all_commands_1(data, for_all))
			return (0);
	}
	else
	{
		print_error("bash: syntax error near unexpected token `|'");
		return (0);
	}
	return (1);
}

/*============================================================================*/

char	*remove_dollar(char *cmd, int start)
{
	int		i;
	char	*new;

	i = 0;
	new = malloc(ft_strlen_n(cmd));
	while ((cmd[i]) && i < start)
	{
		new[i] = cmd[i];
		i++;
	}
	i++;
	while (cmd[i])
	{
		new[i - 1] = cmd[i];
		i++;
	}
	new[i - 1] = 0;
	free(cmd);
	return (new);
}
