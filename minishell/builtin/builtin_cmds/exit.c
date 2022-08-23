/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 03:35:23 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/18 20:50:41 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*============================================================================*/
/**
 * @brief exit command, executed when readline() catch "exit" on terminal
 *
 * @param data
 * @return int
 **=========================================================================**
 **/
static void	exit_utils(t_data *data)
{
	free_global_data();
	fd_closer(data);
	free_cmds(data);
	free_env(g_data->envp);
	free(g_data->envp);
	free(g_data);
	free(data);
	data = NULL;
}

/*============================================================================*/
static void	exit_utils_2(char *str)
{
	ft_putstr_fd("[minishell]:", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_data->return_state = 255;
	free_env(g_data->envp);
	free(g_data->envp);
	free(g_data);
}

/*============================================================================*/
int	ft_exit(t_data *data, int cmd_num)
{
	int	i;

	i = -1;
	if (ft_strcmp(data[cmd_num].s_cmd[0], "exit") == 0)
	{
		if (data[cmd_num].s_cmd[1])
		{
			while (data[cmd_num].s_cmd[1][++i])
			{
				if (!ft_isdigit(data[cmd_num].s_cmd[1][i]))
				{
					exit_utils_2(data[cmd_num].s_cmd[1]);
					free_global_data();
					fd_closer(data);
					free_cmds(data);
					free(data);
					return (1);
				}
			}
			g_data->return_state = ft_atoi(data[cmd_num].s_cmd[1]) % 256;
		}
		exit_utils(data);
		return (1);
	}
	return (0);
}

/*============================================================================*/
