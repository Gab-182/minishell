/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 05:44:06 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/19 22:16:08 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*============================================================================*/

t_data	*check_cmd_utils(t_data *data, char ***cmd_holder)
{
	g_data->pipes_num = count_pipes(g_data->args, g_data->pipes_num);
	data = ft_calloc(sizeof(t_data), (g_data->pipes_num + 1));
	*cmd_holder = ft_split_og(g_data->args, '|');
	return (data);
}

/*============================================================================*/
static void	init_check_cmd(t_dquote *for_all, int *i)
{
	for_all->dquote = 0;
	g_data->pipes_num = 1;
	*i = -1;
}

/*============================================================================*/

static int	heredoc_stopper(t_data *data, int cmd_num)
{
	int	j;

	j = 0;
	if (g_data->i > 1)
		return (0);
	while (data[cmd_num].operator[j])
	{
		if (ft_strncoomp(data[cmd_num].operator[j], "<<", 2) && cmd_num > 0)
			return (0);
		if (ft_strncoomp(data[cmd_num].operator[j], "<<", 2))
		{
			g_data->i++;
			return (1);
		}
		j++;
	}
	return (1);
}

/*============================================================================*/
t_data	*check_cmd(t_data *data)
{
	t_dquote	for_all;
	char		**cmd_holder;
	int			i;

	init_check_cmd(&for_all, &i);
	check_dquote_only(g_data->args, &for_all);
	if (!check_error_status(g_data->pipes_num, g_data->args, &for_all))
		return (0);
	data = check_cmd_utils(data, &cmd_holder);
	while (++i < g_data->pipes_num)
	{
		if (!data_init(&data[i], &for_all, cmd_holder[i], g_data->envp)
			|| !redirect_all_commands(&data[i], &for_all) || \
			!heredoc_stopper(data, i))
		{
			free_2d_array(cmd_holder);
			free_cmds(data);
			free(data);
			data = NULL;
			return (0);
		}
	}
	free_2d_array(cmd_holder);
	execute(data);
	return (data);
}

/*============================================================================*/