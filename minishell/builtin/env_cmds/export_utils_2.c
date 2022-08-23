/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:36:07 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/17 10:56:38 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*============================================================================*/
/**
 * @brief Sorting the environment elements in alphabetical order.
 *
 * @param envp the environment structure
 */
void	sorting_environment(t_envp *envp)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 1;
	while (envp->env[i])
	{
		while (envp->env[j])
		{
			if (ft_strncmp(envp->env[i], envp->env[j], 1) < 0)
			{
				temp = ft_strdup(envp->env[j]);
				free(envp->env[j]);
				envp->env[j] = ft_strdup(envp->env[i]);
				free(envp->env[i]);
				envp->env[i] = ft_strdup(temp);
				free(temp);
			}
			j++;
		}
		j = 0;
		i++;
	}
	temp = NULL;
}

/*============================================================================*/
/**
 * @brief printing the required information when executing export command.
 *
 * @param data the global structure
 */
void	export_print_2(t_envp *envp, int *i, int *j)
{
	ft_putchar_fd('=', STDOUT_FILENO);
	ft_putstr_fd("\"", STDOUT_FILENO);
	(*j)++;
	if (!envp->env[*i][*j])
		ft_putstr_fd("\"", STDOUT_FILENO);
	while (envp->env[*i][*j])
	{
		ft_putchar_fd(envp->env[*i][*j], STDOUT_FILENO);
		(*j)++;
		if (!envp->env[*i][*j])
			ft_putstr_fd("\"", STDOUT_FILENO);
	}
}

/*============================================================================*/
void	export_print(t_envp *envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp->env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (envp->env[i][j] && envp->env[i][j] != '=')
		{
			ft_putchar_fd(envp->env[i][j], STDOUT_FILENO);
			j++;
		}
		if (envp->env[i][j] == '=')
			export_print_2(envp, &i, &j);
		j = 0;
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

/*============================================================================*/
char	*delchar(char *cmd)
{
	int		i;
	char	*new_cmd;
	char	*last_cmd;

	i = 0;
	while (cmd[i] != '=')
		i++;
	new_cmd = ft_substr(cmd, 0, i - 1);
	if (!new_cmd)
	{
		ft_putstr_fd("[minishell]:", STDOUT_FILENO);
		ft_putstr_fd(cmd, STDOUT_FILENO);
		ft_putendl_fd("command not found", STDOUT_FILENO);
	}
	last_cmd = ft_strjoin(new_cmd, ft_strchr(cmd, '='));
	if (new_cmd)
		free(new_cmd);
	new_cmd = NULL;
	return (last_cmd);
}

/*============================================================================*/