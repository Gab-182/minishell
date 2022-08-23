/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:08:41 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/16 03:16:33 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/*============================================================================*/
static int	env_name_search(t_data *data, int index, t_envp *envp)
{
	int		i;
	size_t	env_name_len;

	i = 0;
	while (envp->env[i])
	{
		env_name_len = env_element_name(envp->env, i);
		if (ft_strncmp(envp->env[i], data->s_cmd[index], \
			env_name_len) == 0)
			return (1);
		i++;
	}
	return (0);
}

/*============================================================================*/
int	ft_unset(t_data *data, t_envp *envp, int cmd_num)
{
	int		i;

	i = 0;
	if (ft_strcmp(data[cmd_num].s_cmd[0], "unset") == 0)
	{
		i++;
		while (data[cmd_num].s_cmd[i])
		{
			if (env_name_search(data, i, envp))
				del_from_env(envp, data[cmd_num].s_cmd[i]);
			i++;
		}
		return (1);
	}
	return (0);
}
/*============================================================================*/