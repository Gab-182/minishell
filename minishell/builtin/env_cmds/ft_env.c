/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:53:12 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/16 03:16:33 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*============================================================================*/
/**
 * @brief print every element that contains the (=).
 * add to it (if shell level == 0 pass that)
 * 
 * @param data 
 * @param envp 
 * @param cmd_num 
 * @return int 
 */
int	ft_env(t_data *data, t_envp *envp, int cmd_num)
{
	int	i;

	i = 0;
	if (ft_strcmp(data[cmd_num].s_cmd[0], "env") == 0)
	{
		while (envp->env[i])
		{
			if (ft_strchr(envp->env[i], '='))
				printf("%s\n", envp->env[i]);
			i++;
		}
		return (1);
	}
	return (0);
}

/*============================================================================*/