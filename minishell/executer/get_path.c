/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 20:59:00 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/19 20:22:35 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*============================================================================*/

/**
 ** @brief Get the path for the required command joined with the required
 ** command.
 **
 ** @param path
 ** @param cmd
 ** @return char*
 **=========================================================================**
 */

static void
	get_path_utils(char ***splitted_path, int *i, \
	t_data *data, char **joined_path)
{
	if (*joined_path)
	{
		free(*joined_path);
		*joined_path = NULL;
	}
	if ((*splitted_path)[*i])
		*joined_path = ft_strjoin_mult(3, (*splitted_path)[*i], \
			"/", data->s_cmd[0]);
}

char
	*get_path_2(char ***splitted_path, int *i, t_data *data, char **joined_path)
{
	while (*splitted_path && (*splitted_path)[*i])
	{
		if (data->s_cmd && data->s_cmd[0])
			get_path_utils(splitted_path, i, data, joined_path);
		else
			return (NULL);
		if (access(*joined_path, F_OK) == 0)
			return (*joined_path);
		else
		{
			if (*joined_path)
			{
				free(*joined_path);
				*joined_path = NULL;
			}
		}
		(*i)++;
	}
	return ("for real, i hate norm");
}

/*============================================================================*/
static void	error_message(t_data *data, int cmd_found)
{
	if (!cmd_found)
	{
		ft_putstr_fd("\033[1;31m [minishell]: \033[0m ", 2);
		ft_putstr_fd(data->s_cmd[0], 2);
		ft_putstr_fd(": command not found\033[0m\n", 2);
		g_data->return_state = 127;
	}
}

/*============================================================================*/
/**
 * @brief Get the path object for the required command joined with the command
 * for the execve() function requirements.
 * 
 * @param path 
 * @param data 
 * @param args 
 * @return char* 
 */
char	*get_path(char *path, t_data *data, char *args)
{
	char	**splitted_path;
	char	*joined_path;
	int		cmd_found;
	int		i;

	joined_path = NULL;
	splitted_path = NULL;
	cmd_found = 0;
	if (path && data->s_cmd && data->s_cmd[0] && ft_strlen(args) != 0)
	{
		splitted_path = ft_split(path, ':');
		i = 0;
		if (!ft_strncomp(get_path_2(&splitted_path, &i, data,
					&joined_path), "for real, i hate norm", 21))
			return (get_path_2(&splitted_path, &i, data, &joined_path));
		if (splitted_path)
			free_2d_array(splitted_path);
		error_message(data, cmd_found);
	}
	return (NULL);
}

/*============================================================================*/
