/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 06:53:02 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/19 22:17:42 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*============================================================================*/
static void	init_environment(char **environ)
{
	g_data->i = 0;
	g_data->envp = ft_calloc(1, sizeof(t_envp));
	g_data->envp->env = dup_2darray(environ);
	if (getenv("OLDPWD"))
		del_from_env(g_data->envp, "OLDPWD");
	add_to_env(g_data->envp, "OLDPWD");
	if (is_excited(g_data->envp, "SHLVL"))
	{
		g_data->envp->shlvl = ft_atoi(getenv("SHLVL"));
		add_to_shlvl();
		shlvl_edge_cases(g_data->envp);
	}
	else
		add_to_env(g_data->envp, "SHLVL=1");
}

/*============================================================================*/
/**
 * @brief Check the enf of the file, [Ctrl+D] signal
 *
 * @param g_data
 */
void	eof_checker(t_data **data)
{
	if (!g_data->args)
	{
		ft_putstr_fd(Y"exit\n"RESET, 1);
		free_global_data();
		free(*data);
		*data = NULL;
		free_env(g_data->envp);
		free(g_data->envp);
		free(g_data);
		exit(0);
	}
}

/*============================================================================*/
/**
 * @brief The loop for readline()
 *
 * @param data
 */
static void	reading(t_data **data)
{
	while (1)
	{
		g_data->printed_path = print_path();
		g_data->args = readline(g_data->printed_path);
		eof_checker(&*data);
		if (ft_strlen(g_data->args) && checker(g_data->args)
			&& g_data->args[0] != '\r' && g_data->args[0] != '\t')
		{
			if (g_data->args && ft_strlen(g_data->args))
				add_history(g_data->args);
			*data = check_cmd(*data);
			if (*data == 0)
			{
				free(*data);
				*data = NULL;
				free_global_data();
				continue ;
			}
			free_cmds(*data);
			fd_closer(*data);
			free(*data);
			*data = NULL;
		}	
		free_global_data();
	}
}

/*============================================================================*/
int	main(int argc, char **argv, char **environ)
{
	t_data	*data;

	g_data = ft_calloc(1, sizeof(t_gd));
	data = NULL;
	if (argc != 1)
	{
		ft_putstr_fd("\033[1;31m [minishell]: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(" : No such file or directory \033[0m", 2);
		return (127);
	}
	g_data->return_state = 0;
	handle_signals();
	init_environment(environ);
	reading(&data);
	free_env(g_data->envp);
	free_cmds(data);
	fd_closer(data);
	free(g_data);
	free(data);
	return (EXIT_SUCCESS);
}

/*============================================================================*/
