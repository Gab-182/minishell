/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 05:18:42 by isaad             #+#    #+#             */
/*   Updated: 2022/08/19 21:03:32 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*============================================================================*/

static void	if_escape(char **f, int *i, t_data *data)
{
	if ((*f)[*i] == '$' && (*f)[*i + 1] == '?')
	{
		(*i)++;
		*f = check_expand_1(*i, *f, data->env);
		*i = 0;
	}
}

/*============================================================================*/
char	*check_expand_helper_final(char *f, int *i, t_data *data)
{
	while (f[i[0]])
	{
		if_escape(&f, &(i[0]), data);
		if (f[i[0]] == '$' && ft_isdigit(f[i[0] + 1]))
		{
			i[0]++;
			f = check_expand_1(i[0], f, data->env);
			i[0] = 0;
		}
		else if (f[i[0]] == 34)
			f = check_expand_helper_2(f, i, data);
		else if (f[i[0]] == 39)
			i[0] = check_expand_helper_1(f, i);
		else if (f[i[0]] == '$' && isenv(f[i[0] + 1]))
		{
			i[0]++;
			f = check_expand_1(i[0], f, data->env);
			i[0] = 0;
		}
		else if (f[i[0]] == '$' && (f[i[0] + 1] == 34 || f[i[0] + 1] == 39))
			f = remove_dollar(f, i[0]);
		else
			i[0]++;
	}
	return (f);
}

/*============================================================================*/

char	*no_expand_found(char **cmd, int start, int length)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(ft_strlen(*cmd) - length);
	while (i < start - 1 && (*cmd)[i])
	{
		new_str[j] = (*cmd)[i];
		i++;
		j++;
	}
	i += length + 1;
	while ((*cmd)[i])
	{
		new_str[j] = (*cmd)[i];
		j++;
		i++;
	}
	new_str[j] = 0;
	free(*cmd);
	return (new_str);
}

/*============================================================================*/

static void	util_exp(char **cmd, int *i, char **new_str, int *j)
{
	while ((*cmd)[*i])
	{
		(*new_str)[*j] = (*cmd)[*i];
		(*j)++;
		(*i)++;
	}
}

char	*edit_expanded(char *expanded, char *cmd, int length, int start)
{
	int		index;
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	if (cmd[start] == '?')
	{
		index = 0;
		new_str = malloc(ft_strlen(cmd) - length + ft_strlen(expanded));
	}
	else
	{
		index = length + 1;
		new_str = malloc(ft_strlen(cmd) - length + ft_strlen(expanded) + 1);
	}
	while (i < start - 1 && cmd[i])
		new_str[j++] = cmd[i++];
	while (expanded[index])
		new_str[j++] = expanded[index++];
	i += length + 1;
	util_exp(&cmd, &i, &new_str, &j);
	new_str[j] = 0;
	return (new_str);
}

/*============================================================================*/
