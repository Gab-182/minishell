/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cleaner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:22:07 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/16 03:16:33 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*============================================================================*/
/**
 * @brief Free 2D array safely.
 * 
 * @param array 
 */
void	free_2d_array(char **array)
{
	int	i;

	if (array)
	{
		i = 0;
		while (array[i] != NULL)
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
		free(array);
		array = NULL;
	}
}

/*============================================================================*/
/**
 * @brief Free the environment [env] inside the envp structure
 * 
 * @param envp environment structure
 */
void	free_env(t_envp *envp)
{
	int	i;

	if (envp->env != NULL)
	{
		i = 0;
		while (envp->env[i] != NULL)
		{
			free(envp->env[i]);
			envp->env[i] = NULL;
			i++;
		}
		free(envp->env);
		envp->env = NULL;
	}
}

/*============================================================================*/
/**
 * @brief free operator from all the structs
 * 
 * @param data 
 * @param cmd_num 
 */
void	free_struct_operator(t_data *data, int cmd_num)
{
	int	i;

	i = 0;
	if (data[cmd_num].operator)
	{
		while (data[cmd_num].operator[i] != NULL)
		{
			free(data[cmd_num].operator[i]);
			data[cmd_num].operator[i] = NULL;
			i++;
		}
		free(data[cmd_num].operator);
		data[cmd_num].operator = NULL;
	}
}

/*============================================================================*/
/**
 * @brief free file_name from all the structs
 * 
 * @param data 
 * @param cmd_num 
 */
void	free_struct_file_name(t_data *data, int cmd_num)
{
	int	i;

	i = 0;
	if (data[cmd_num].file_name)
	{
		while (data[cmd_num].file_name[i] != NULL)
		{
			free(data[cmd_num].file_name[i]);
			data[cmd_num].file_name[i] = NULL;
			i++;
		}
		free(data[cmd_num].file_name);
		data[cmd_num].file_name = NULL;
	}
}

/*============================================================================*/
/**
 * @brief free s_cmd from all the structs
 * 
 * @param data 
 * @param cmd_num 
 */
void	free_struct_s_cmd(t_data *data, int cmd_num)
{
	int	i;

	i = 0;
	if (data[cmd_num].s_cmd)
	{
		while (data[cmd_num].s_cmd[i] != NULL)
		{
			free(data[cmd_num].s_cmd[i]);
			i++;
		}
		free(data[cmd_num].s_cmd);
	}
}

/*============================================================================*/