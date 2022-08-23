/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:52:14 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/14 06:15:28 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief  * @brief updating the shell level inside the env variables whenever 
 * executing another shell inside the current one
 */
/*============================================================================*/
void	shlvl_edge_cases(t_envp *envp)
{
	char	*shlvl;

	if (envp->shlvl == 999)
	{
		del_from_env(envp, "SHLVL=");
		add_to_env(envp, "SHLVL=");
	}
	else if (envp->shlvl == 1000)
	{
		del_from_env(envp, "SHLVL=");
		add_to_env(envp, "SHLVL=");
	}
	else if (envp->shlvl > 999)
	{
		shlvl = env_value(envp, "SHLVL");
		ft_putstr_fd("[minishell]: warning: shell level (", STDOUT_FILENO);
		ft_putstr_fd(shlvl + 1, STDOUT_FILENO);
		ft_putendl_fd(") too high, resetting to 1", STDOUT_FILENO);
		del_from_env(envp, "SHLVL=");
		add_to_env(envp, "SHLVL=1");
		free(shlvl);
		shlvl = NULL;
	}
}

/*============================================================================*/
void	add_to_shlvl(void)
{
	char	*shell_level;
	char	*shl;

	g_data->envp->shlvl += 1;
	shl = ft_itoa(g_data->envp->shlvl);
	del_from_env(g_data->envp, "SHLVL=");
	shell_level = ft_strjoin("SHLVL=", shl);
	free(shl);
	shl = NULL;
	add_to_env(g_data->envp, shell_level);
	free(shell_level);
	shell_level = NULL;
}

/*============================================================================*/
