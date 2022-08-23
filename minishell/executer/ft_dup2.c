/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:47:43 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/16 05:19:13 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*============================================================================*/
static void	first_cmd(t_data *data, int cmd_num)
{
	if (dup2(data[cmd_num].fd[1], STDOUT_FILENO) < 0)
	{
		perror("\033[1;31m [minishell] \033[0m");
		exit(EXIT_FAILURE);
	}
	close(data[cmd_num].fd[1]);
	data[cmd_num].fd[1] = 0;
}

/*============================================================================*/
static void	last_cmd(t_data *data, int cmd_num)
{
	if (dup2(data[cmd_num - 1].fd[0], STDIN_FILENO) < 0)
	{
		perror("\033[1;31m [minishell] \033[0m");
		exit(EXIT_FAILURE);
	}
	close(data[cmd_num - 1].fd[0]);
	data[cmd_num - 1].fd[0] = 0;
}

/*============================================================================*/
static void	middle_cmds(t_data *data, int cmd_num)
{
	if (dup2(data[cmd_num - 1].fd[0], STDIN_FILENO) < 0)
	{
		perror("\033[1;31m [minishell] \033[0m");
		exit(EXIT_FAILURE);
	}
	if (dup2(data[cmd_num].fd[1], STDOUT_FILENO) < 0)
	{
		perror("\033[1;31m [minishell] \033[0m");
		exit(EXIT_FAILURE);
	}
	close(data[cmd_num - 1].fd[0]);
	close(data[cmd_num].fd[1]);
	data[cmd_num - 1].fd[0] = 0;
	data[cmd_num].fd[1] = 0;
}

/*============================================================================*/
void	ft_dup2(t_data *data, int cmd_num)
{
	if (g_data->pipes_num != 1)
	{
		if (cmd_num == 0)
			first_cmd(data, cmd_num);
		else if (cmd_num + 1 == g_data->pipes_num)
			last_cmd(data, cmd_num);
		else
			middle_cmds(data, cmd_num);
	}
}

/*============================================================================*/