/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 08:33:57 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/16 01:36:34 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*============================================================================*/
/**
 * @brief Check if the given variable is excited inside the environment, 
 * if so return (1) else return (0)
 * 
 * @param envp environment structure
 * @param to_compare 
 * @return int 
 */
int	is_excited(t_envp *envp, char *to_compare)
{
	int	i;
	int	element_len;

	i = 0;
	while (envp->env[i])
	{
		element_len = env_element_name(envp->env, i);
		if (ft_strncmp(envp->env[i], to_compare, element_len) == 0)
			return (1);
		i++;
	}
	return (0);
}

/*============================================================================*/
/**
 * @brief return the length of the desired element name from the env.
 * [the total name befor the (=) sign]
 *
 * @param env
 * @param index
 * @return int
 */
size_t	env_element_name(char **env, int index)
{
	size_t	i;

	i = 0;
	if (ft_strchr(env[index], '='))
	{
		while (env[index][i] && env[index][i] != '=')
			i++;
	}
	else
		i = ft_strlen(env[index]);
	return (i);
}

/*============================================================================*/
/**
 * @brief return the value for an environment element
 *
 * @param envp the environment structure
 * @param element_name the environment element name
 * @return char*
 */
char	*env_value(t_envp *envp, char *element_name)
{
	char	*value;
	size_t	env_name_len;
	int		i;

	i = 0;
	value = NULL;
	while (envp->env[i])
	{
		env_name_len = env_element_name(envp->env, i);
		if (ft_strncmp(envp->env[i], element_name, env_name_len) == 0)
		{
			value = ft_strdup(ft_strchr(envp->env[i], '='));
			break ;
		}
		i++;
	}
	return (value);
}

/*============================================================================*/