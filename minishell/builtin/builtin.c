/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 08:26:50 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/18 20:22:48 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*============================================================================*/
/**
 * @brief Check if the command is a built in command,
 * if it is a built in, return 1, else return 0
 * 
 * @param data array of global structure
 * @param envp environment structure
 * @param cmd_num readline result
 * @return int 
 */
int	builtin_checker(t_data *data, int cmd_num)
{
	if (data[cmd_num].s_cmd && data[cmd_num].s_cmd[0])
	{
		if (ft_strcmp(data[cmd_num].s_cmd[0], "cd") == 0
			|| strcmp(data[cmd_num].s_cmd[0], "echo") == 0
			|| ft_strcmp(data[cmd_num].s_cmd[0], "pwd") == 0
			|| ft_strcmp(data[cmd_num].s_cmd[0], "env") == 0
			|| ft_strcmp(data[cmd_num].s_cmd[0], "unset") == 0
			|| ft_strcmp(data[cmd_num].s_cmd[0], "export") == 0
			|| ft_strcmp(data[cmd_num].s_cmd[0], "exit") == 0)
			return (1);
	}
	return (0);
}

/*============================================================================*/
/**
 * @brief same as the built_in(), the only difference is that this one,
 * closes the child after execution.
 * 
 * @param data array of global structure
 * @param envp environment structure
 * @param cmd_num readline result
 * @return int 
 */
static int	forked_builtin(t_data *data, int cmd_num)
{
	if (ft_cd(data, g_data->envp, cmd_num) \
	|| ft_echo(data, cmd_num) \
	|| ft_pwd(data, cmd_num) \
	|| ft_env(data, g_data->envp, cmd_num) \
	|| ft_unset(data, g_data->envp, cmd_num) \
	|| ft_export(data, g_data->envp, cmd_num))
	{
		fd_closer(data);
		exit (EXIT_SUCCESS);
	}
	else if (ft_exit(data, cmd_num))
		exit (g_data->return_state);
	fd_closer(data);
	exit (EXIT_FAILURE);
}

/*============================================================================*/
int	piped_built_in(t_data *data, int cmd_num)
{
	pid_t	built_in_pid;

	built_in_pid = fork();
	if (built_in_pid < 0)
	{
		perror("\033[1;31m [minishell] \033[0m");
		exit(-1);
	}
	else if (built_in_pid == 0)
	{
		ft_dup2(data, cmd_num);
		check_redirection(data, cmd_num);
		forked_builtin(data, cmd_num);
		fd_closer(data);
	}
	return (1);
}

/*============================================================================*/
int	builtin(t_data *data, int cmd_num)
{
	int	i;

	i = g_data->return_state;
	if (ft_cd(data, g_data->envp, cmd_num) \
	|| ft_echo(data, cmd_num) \
	|| ft_pwd(data, cmd_num) \
	|| ft_env(data, g_data->envp, cmd_num) \
	|| ft_unset(data, g_data->envp, cmd_num) \
	|| ft_export(data, g_data->envp, cmd_num))
		return (1);
	else if (ft_exit(data, cmd_num))
		exit (i);
	return (0);
}

/*============================================================================*/
