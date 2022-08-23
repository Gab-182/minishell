/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 23:51:57 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/18 18:46:28 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*============================================================================*/
static int	is_flag(char *cmd)
{
	int		i;

	i = 0;
	if (cmd[i] == '-' && cmd[i + 1] != 'n')
		return (1);
	if (cmd[i] != '-')
		return (1);
	i++;
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

/*============================================================================*/
static void	dollar_detector(t_data *data, int i, int cmd_num)
{
	int	j;

	j = 0;
	while (data[cmd_num].s_cmd[i][j])
	{
		if (data[cmd_num].s_cmd[i][j] == '$'
			&& data[cmd_num].s_cmd[i][j + 1] == '?')
		{
			ft_putnbr_fd(g_data->return_state, 1);
			g_data->return_state = 0;
			j++;
		}
		else if (data[cmd_num].s_cmd[i][j])
			ft_putchar_fd(data[cmd_num].s_cmd[i][j], 1);
		j++;
	}
}

/*============================================================================*/
static void	flag_scraper(t_data *data, int *cmd_num, int *i, int *newline)
{
	while (data[*cmd_num].s_cmd[*i]
		&& !is_flag(data[*cmd_num].s_cmd[*i]))
	{
		*newline = 1;
		(*i)++;
	}
}

/*============================================================================*/
int	ft_echo(t_data *data, int cmd_num)
{
	int	i;
	int	newline;

	i = 1;
	newline = 0;
	if (strcmp(data[cmd_num].s_cmd[0], "echo") == 0)
	{
		flag_scraper(data, &cmd_num, &i, &newline);
		while (data[cmd_num].s_cmd[i])
		{
			dollar_detector(data, i, cmd_num);
			if (data[cmd_num].s_cmd[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
		if (!newline)
			ft_putstr_fd("\n", 1);
		g_data->return_state = 0;
		return (1);
	}
	return (0);
}

/*============================================================================*/