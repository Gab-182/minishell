/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 19:06:26 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/19 19:16:03 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*============================================================================*/
static int	absolute_path(t_data *data, int cmd_num)
{
	if (data[cmd_num].s_cmd && data[cmd_num].s_cmd[0])
	{
		if (!access(data[cmd_num].s_cmd[0], F_OK))
		{
			if (execve(data[cmd_num].s_cmd[0],
					data[cmd_num].s_cmd, g_data->envp->env) < 0)
			{
				ft_putstr_fd("\033[1;31m [minishell]: \033[0m ", 2);
				perror(data[cmd_num].s_cmd[0]);
				fd_closer(data);
				free_cmds(data);
				free(data);
				exit(EXIT_FAILURE);
			}
			return (1);
		}
	}
	return (0);
}

/*============================================================================*/
/**
 * @brief Handling executing executable files from the same path.
 * example: ./minishell
 * 
 * @param data 
 * @param environ 
 */
static void	slash_command(t_data *data, int cmd_num)
{
	if (data[cmd_num].s_cmd && data[cmd_num].s_cmd[0] && ft_strncmp
		(data[cmd_num].s_cmd[0], "./", 2) == 0)
	{
		if (execve(data[cmd_num].s_cmd[0],
				data[cmd_num].s_cmd, g_data->envp->env) < 0)
		{
			ft_putstr_fd("\033[1;31m [minishell]: \033[0m ", 2);
			perror(data[cmd_num].s_cmd[0]);
		}
		fd_closer(data);
		free_cmds(data);
		free(data);
		exit(127);
	}
}

/*============================================================================*/
/**
 * @brief 
 ** The execution of the child proccess.
 ** [1] Make the return status == 0
 ** [2] at the beginning check if the path is not NULL
 ** [3] If the path is null => then terminate and exit the child proccess.
 ** [4] if the command not found, return status should be (127).
 * 
 * @param data The array of global structure.
 * @param environ The environment structure.
 * @param args the readline result
 * @param cmd_num The number of the structure.
 */
static void	ft_child_exec(t_data *data, int cmd_num)
{
	char	*envir_value;

	absolute_path(data, cmd_num);
	envir_value = env_value(g_data->envp, "PATH");
	slash_command(data, cmd_num);
	if (data[cmd_num].s_cmd && data[cmd_num].s_cmd[0])
	{
		data[cmd_num].path = get_path(envir_value, &data[cmd_num], \
					g_data->args);
		if (data[cmd_num].path)
		{
			if (execve(data[cmd_num].path, data[cmd_num].s_cmd, \
					g_data->envp->env) < 0)
			{
				ft_putstr_fd("\033[1;31m [minishell]: \033[0m ", 2);
				ft_putstr_fd(data->s_cmd[0], 2);
				ft_putstr_fd(": command not found\033[0m\n", 2);
			}
		}
	}
	free(envir_value);
	fd_closer(data);
	free_cmds(data);
	g_data->return_state = 127;
	exit(127);
}

/*============================================================================*/
void	fork_child(t_data *data, int cmd_num)
{
	pid_t	child_pid;

	if (data[cmd_num].s_cmd && data[cmd_num].s_cmd[0] && \
			data[cmd_num].s_cmd[0][0])
	{
		child_pid = fork();
		if (child_pid < 0)
		{
			perror("\033[1;31m [minishell] \033[0m");
			exit(-1);
		}
		else if (child_pid == 0)
		{
			ft_dup2(data, cmd_num);
			check_redirection(data, cmd_num);
			fd_closer(data);
			ft_child_exec(data, cmd_num);
		}
	}
}

/*============================================================================*/