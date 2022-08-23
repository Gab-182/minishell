/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 05:05:00 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/19 08:02:39 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*============================================================================*/
static void	add_it(t_data *data, int cmd_num, t_envp *envp, int i)
{
	if (already_exist(data[cmd_num].s_cmd[i], envp))
	{
		if (ft_strchr(data[cmd_num].s_cmd[i], '='))
		{
			del_from_env(envp, data[cmd_num].s_cmd[i]);
			add_to_env(envp, data[cmd_num].s_cmd[i]);
		}
	}
	else
		add_to_env(envp, data[cmd_num].s_cmd[i]);
}

/*============================================================================*/
static void	edit_it(t_envp *envp, t_data *data, int cmd_num, int i)
{
	char	*edited_command;

	edited_command = delchar(data[cmd_num].s_cmd[i]);
	add_to_env(envp, edited_command);
	free(edited_command);
	edited_command = NULL;
}

/*============================================================================*/
static int	printing(t_envp *envp, t_data *data, int cmd_num, int i)
{
	if (!data[cmd_num].s_cmd || !data[cmd_num].s_cmd[i])
	{
		sorting_environment(envp);
		export_print(envp);
		return (1);
	}
	return (5);
}

/*============================================================================*/
static void	check_it(t_envp *envp, t_data *data, int cmd_num, int i)
{
	if (already_exist(data[cmd_num].s_cmd[i], envp))
		add_to_env_value(envp, data[cmd_num].s_cmd[i]);
	else
		edit_it(envp, data, cmd_num, i);
}

/*============================================================================*/
int	ft_export(t_data *data, t_envp *envp, int cmd_num)
{
	int		i;
	int		valid;

	i = 0;
	if (ft_strcmp(data[cmd_num].s_cmd[i], "export") == 0)
	{
		i++;
		if (printing(envp, data, cmd_num, i) != 5)
			return (1);
		while (data[cmd_num].s_cmd[i])
		{
			valid = valid_toadd(&data[cmd_num], i);
			if (valid == 1)
				add_it(data, cmd_num, envp, i);
			else if (valid == 2)
				check_it(envp, data, cmd_num, i);
			i++;
		}
		return (1);
	}
	return (0);
}

/*============================================================================*/
