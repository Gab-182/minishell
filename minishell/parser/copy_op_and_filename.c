/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_op_and_filename.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 05:18:34 by isaad             #+#    #+#             */
/*   Updated: 2022/08/19 20:30:11 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*============================================================================*/
int	copy_details(t_data *data)
{
	int	nb_of_op;
	int	x;

	x = 0;
	nb_of_op = count_op(data);
	while (x < nb_of_op)
	{
		allocate_op_and_file(data, x);
		copy_op_and_file(data, x);
		x++;
	}
	return (0);
}

/*============================================================================*/
void	allocate_op_and_file(t_data *data, int x)
{
	int	i;
	int	size_for_op;
	int	size_for_file;

	i = 0;
	size_for_op = 0;
	size_for_file = 0;
	while (data->full_op[x][i] == '>' || data->full_op[x][i] == '<')
	{
		i++;
		size_for_op++;
	}
	data->operator[x] = malloc(size_for_op + 1);
	i++;
	while (data->full_op[x][i])
	{
		i++;
		size_for_file++;
	}
	data->file_name[x] = malloc(size_for_file + 1);
}

/*============================================================================*/
void	copy_op_and_file(t_data *data, int x)
{
	int	i;
	int	size_for_op;
	int	size_for_file;

	i = 0;
	size_for_op = 0;
	size_for_file = 0;
	while (data->full_op[x][i] == '>' || data->full_op[x][i] == '<')
	{
		data->operator[x][size_for_op] = data->full_op[x][i];
		i++;
		size_for_op++;
	}
	data->operator[x][size_for_op] = 0;
	i++;
	while (data->full_op[x][i])
	{
		data->file_name[x][size_for_file] = data->full_op[x][i];
		i++;
		size_for_file++;
	}
	data->file_name[x][size_for_file] = 0;
}

/*============================================================================*/
/*============================================================================*/

static void	utils(char **to_expand, char **expanded, int i, char **cmd)
{
	if (*to_expand)
	{
		free(*to_expand);
		*to_expand = NULL;
	}
	if (*expanded && (*cmd)[i] == '?')
	{
		free(*expanded);
		*expanded = NULL;
	}
	free(*cmd);
	*cmd = NULL;
}

char	*replace_sub_str_to_expand(char *cmd, int start, int length, char **env)
{
	int		i;
	char	*new_str;
	char	*to_expand;
	char	*expanded;

	i = start;
	new_str = NULL;
	to_expand = ft_strndup(cmd, length, i);
	if (cmd[i] == '?')
		expanded = ft_itoa(g_data->return_state);
	else
		expanded = ft_getenv(to_expand, env);
	if (expanded == NULL)
	{
		if (to_expand)
		{
			free(to_expand);
			to_expand = NULL;
		}
		return (no_expand_found(&cmd, start, length));
	}
	if (expanded)
		new_str = edit_expanded(expanded, cmd, length, start);
	utils(&to_expand, &expanded, i, &cmd);
	return (new_str);
}

/*============================================================================*/