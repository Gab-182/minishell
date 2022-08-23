/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 02:22:55 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/16 03:16:33 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*============================================================================*/
static void	edit_pwd(char *old_pwd, char *new_pwd)
{
	del_from_env(g_data->envp, "PWD=");
	del_from_env(g_data->envp, "OLDPWD=");
	add_to_env(g_data->envp, old_pwd);
	add_to_env(g_data->envp, new_pwd);
}

/*============================================================================*/
/**
 * @brief update the (PWD) and (OLDPWD) when using (cd) command.
 * 
 * @param envp the Environment structure.
 */
static void	update_path(t_envp *envp)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*pwd_value;
	char	*path;

	pwd_value = env_value(envp, "PWD=");
	if (pwd_value)
	{
		path = getcwd(NULL, 0);
		old_pwd = ft_strjoin("OLDPWD", pwd_value);
		new_pwd = ft_strjoin("PWD=", path);
		edit_pwd(old_pwd, new_pwd);
		free(new_pwd);
		free(old_pwd);
		free(path);
		path = NULL;
		new_pwd = NULL;
		old_pwd = NULL;
	}
	if (pwd_value)
	{
		free(pwd_value);
		pwd_value = NULL;
	}
}

/*============================================================================*/
/**
 ** If the buffer of getcwd is set to NULL and the size of getcwd is set to 0,
 ** the buffer will be malloc'd of an array with the right size of the input
 ** given for the current working directory.
 **=========================================================================**
 */
int	ft_cd(t_data *data, t_envp *envp, int cmd_num)
{
	if (data[cmd_num].s_cmd[0])
	{
		if (ft_strcmp(data[cmd_num].s_cmd[0], "cd") == 0)
		{
			if (!data[cmd_num].s_cmd[1]
				|| ft_strcmp(data->s_cmd[1], "~") == 0)
				chdir(getenv("HOME"));
			else if (chdir(data[cmd_num].s_cmd[1]) < 0)
				perror(data[cmd_num].s_cmd[1]);
			update_path(envp);
			return (1);
		}
	}
	return (0);
}

/*============================================================================*/