/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hereDoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 01:48:43 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/18 12:51:20 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*============================================================================*/
static void	fd_herdoc_closer(int *fd)
{
	if (fd[1] != 0)
	{
		close(fd[1]);
		fd[1] = 0;
	}
	if (fd[0] != 0)
	{
		close(fd[0]);
		fd[0] = 0;
	}
}

/*============================================================================*/

/*============================================================================*/
int	ft_strncoomp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && i < n && s1[i] == s2[i])
		i++;
	if (i == n && s1[i] == 0 && s2[i] == 0)
		return (1);
	return (0);
}

/*============================================================================*/
int	ft_here_doc(char *str, int fd[2], t_data *data, int cmd_num)
{
	char	*buffer;

	buffer = ft_strdup("");
	while (!ft_strncoomp(str, buffer, ft_strlen(str)))
	{
		free(buffer);
		buffer = NULL;
		buffer = readline("> ");
		if (buffer)
		{
			ft_putstr_fd(buffer, fd[1]);
			write(fd[1], "\n", 1);
		}
	}
	free(buffer);
	if (builtin_checker(data, cmd_num))
		fd_herdoc_closer(fd);
	return (0);
}

int	ft_here_doc_2(char *str)
{
	char	*buffer;

	buffer = ft_strdup("");
	while (!ft_strncoomp(str, buffer, ft_strlen(str)))
	{
		free(buffer);
		buffer = readline("> ");
	}
	free(buffer);
	return (0);
}

/*============================================================================*/
int	heredoc_exec(t_data *data, char *str, int cmd_num)
{
	int	fd[2];
	int	status;

	pipe(fd);
	ft_here_doc(str, fd, data, cmd_num);
	g_data->return_state = WEXITSTATUS(status);
	if (builtin_checker(data, cmd_num) == 0)
		dup2(fd[0], 0);
	if (!builtin_checker(data, cmd_num))
		fd_herdoc_closer(fd);
	return (g_data->return_state);
}

/*============================================================================*/
