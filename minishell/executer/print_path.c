/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:38:03 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/17 08:08:02 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*============================================================================*/
/**
 ** @brief print the path after the (minishell) in different color
 ** 
 ** @return char* 
 **=========================================================================**
 */
char	*print_path(void)
{
	char	*joined_path;
	char	*short_path;
	char	*path;
	char	*h_path;

	path = getcwd(NULL, 0);
	h_path = getenv("HOME");
	if (ft_strncmp(h_path, path, ft_strlen(h_path)) == 0)
	{
		short_path = ft_substr(path, ft_strlen(h_path) + 1, \
			ft_strlen(path) - ft_strlen(h_path));
		joined_path = ft_strjoin_mult(3, "\n【minishell】➤➤(~/", \
						short_path, ")➤➤ ");
		free(short_path);
		short_path = NULL;
	}
	else
		joined_path = ft_strjoin_mult(3, "\n【minishell】➤➤(", path, ")➤➤ ");
	free(path);
	path = NULL;
	return (joined_path);
}

/*============================================================================*/