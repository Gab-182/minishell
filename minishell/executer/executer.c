/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 12:49:25 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/19 19:15:51 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*============================================================================*/
void	ft_wait_all(void)
{
	while (waitpid(-1, &g_data->return_state, 0) > -1)
		g_data->return_state = WEXITSTATUS(g_data->return_state);
}

/*============================================================================*/
/**
 * @brief open a pipe if there is more than one (data)structure.
 * 
 * @param data array of global structure
 * @param cmd_num readline result
 * @return int 
 */
static int	ft_pipe(t_data *data, int cmd_num)
{
	if (cmd_num + 1 != g_data->pipes_num)
	{
		if (pipe(data[cmd_num].fd) == -1)
		{
			perror("\033[1;31m [minishell] \033[0m");
			exit(EXIT_FAILURE);
		}
		return (1);
	}
	return (0);
}

/*============================================================================*/
static void	start_executing(t_data *data)
{
	int	cmd_num;

	cmd_num = 0;
	while (cmd_num < g_data->pipes_num)
	{
		ft_pipe(data, cmd_num);
		if (g_data->pipes_num > 1)
		{
			if (builtin_checker(data, cmd_num))
			{
				piped_built_in(data, cmd_num);
				cmd_num++;
				continue ;
			}
		}
		else if (data[cmd_num].s_cmd && builtin_checker(data, cmd_num))
		{
			check_redirection(data, cmd_num);
			builtin(data, cmd_num);
			cmd_num++;
			continue ;
		}
		fork_child(data, cmd_num);
		cmd_num++;
	}
}

/*============================================================================*/
/**
 * @brief Start the program executing after parsing every thing.
 * the call for this function exist inside the parser.c
 * 
 * @param data the global structure
 * @param cmd_line the argument from the readline function
 * @return int 
 */
int	execute(t_data *data)
{
	g_data->fd_temp = dup(STDOUT_FILENO);
	start_executing(data);
	dup2(g_data->fd_temp, STDOUT_FILENO);
	fd_closer(data);
	ft_wait_all();
	return (1);
}

/*============================================================================*/