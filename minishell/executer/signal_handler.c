/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 19:53:53 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/18 14:08:51 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*============================================================================*/
/**
 ** 2   --> SIGINT Ctrl+C
 ** 3   --> SIGQUIT Ctrl+\
 ** EOF --> Ctrl+D, readline return NULL.
 *? The handling of EOF happening in the mini_parser.
 **=========================================================================**
 */
static void	ft_signal_handler(int sig)
{
	if (sig == 2)
	{
		if (waitpid(-1, &g_data->return_state, WNOHANG) == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			write(2, "  \n\n", 4);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			g_data->return_state = 1;
		}
	}
	else if (sig == 3)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b", 2);
		g_data->return_state = 131;
	}
	else if (sig == 11)
	{
		printf("\033[1;31m*** _____SEGMENTATION_____FAULT_____ ***\n");
		exit(EXIT_FAILURE);
	}
}

/*============================================================================*/
void	handle_signals(void)
{
	signal(2, ft_signal_handler);
	signal(3, ft_signal_handler);
	signal(11, ft_signal_handler);
}

/*============================================================================*/