/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 10:17:23 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/16 03:16:33 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*============================================================================*/
/**
 ** @brief Implementation of pwd command
 ** Note: the max size of the path is limited in linux to 4096 characters 
 ** including the null.
 ** @param cmd 
 **=========================================================================**
 */
int	ft_pwd(t_data *data, int cmd_num)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (data[cmd_num].s_cmd[0])
	{
		if (ft_strcmp(data[cmd_num].s_cmd[0], "pwd") == 0)
		{
			ft_putendl_fd(path, 1);
			free(path);
			path = NULL;
			return (1);
		}
	}
	free(path);
	path = NULL;
	return (0);
}

/*============================================================================*/