/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 19:02:13 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/19 22:19:35 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*============================================================================*/
void	fd_rd_closer(t_data *data, int cmd_num)
{
	if (data[cmd_num].fd_rd != 0)
	{
		close(data[cmd_num].fd_rd);
		data[cmd_num].fd_rd = 0;
	}
}

/*============================================================================*/
void	fd_temp_closer(void)
{
	if (g_data->fd_temp != 0)
	{
		close (g_data->fd_temp);
		g_data->fd_temp = 0;
	}
}

/*============================================================================*/
/**
 * @brief Close the file descriptors for all the structures, but call close
 * function if they are already closed
 * after closing them, assign the closed one to 0
 *
 * @param data
 */
void	fd_closer(t_data *data)
{
	int	i;

	i = 0;
	while (i < g_data->pipes_num - 1)
	{
		if (data[i].fd[0] != 0)
		{
			close (data[i].fd[0]);
			data[i].fd[0] = 0;
		}
		if (data[i].fd[1] != 0)
		{
			close (data[i].fd[1]);
			data[i].fd[1] = 0;
		}
		if (data[i].fd_rd != 0)
		{
			close (data[i].fd_rd);
			data[i].fd_rd = 0;
		}
		i++;
	}
	fd_temp_closer();
}

/*============================================================================*/
/**
 * @brief free all the allocated memory by the array of data structs.
 *
 * @param data
 */
void	free_cmds(t_data *data)
{
	int	cmd_num;

	cmd_num = 0;
	while (cmd_num < g_data->pipes_num)
	{
		free_struct_operator(data, cmd_num);
		free_struct_file_name(data, cmd_num);
		free_struct_s_cmd(data, cmd_num);
		cmd_num++;
	}
}

/*============================================================================*/
void	free_global_data(void)
{
	g_data->i = 0;
	if (g_data->printed_path)
	{
		free(g_data->printed_path);
		g_data->printed_path = NULL;
	}
	if (g_data->args)
	{
		free(g_data->args);
		g_data->args = NULL;
	}
}

/*============================================================================*/
