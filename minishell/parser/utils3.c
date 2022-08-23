/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 05:19:28 by isaad             #+#    #+#             */
/*   Updated: 2022/08/19 12:06:42 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*============================================================================*/
int	isenv(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c
		== '_' || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

/*============================================================================*/
int	ft_strncomp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && i < n && s1[i] == s2[i])
		i++;
	if (i == n)
		return (1);
	return (0);
}

/*============================================================================*/
char	*check_expand_helper_2(char *final_expanded, int *i, t_data *data)
{
	i[1] = 34;
	i[0]++;
	i[2] = i[0];
	final_expanded = check_expand_helper_0(final_expanded, i, data);
	i[0] = check_expand_helper_01(final_expanded, i, data);
	i[0]++;
	return (final_expanded);
}

/*============================================================================*/
char	*ft_strndup(char *cmd, int length, int i)
{
	int		j;
	char	*to_expand;

	j = 0;
	to_expand = malloc(sizeof(char) * length + 1);
	while (cmd[i] && (j < length))
	{
		to_expand[j] = cmd[i];
		i++;
		j++;
	}
	to_expand[j] = 0;
	return (to_expand);
}

/*============================================================================*/
char	*check_expand(char *cmd, t_data *data)
{
	int		i[3];
	char	*final_expanded;

	i[0] = 0;
	if (!checker(cmd))
		return (NULL);
	final_expanded = cmd;
	final_expanded = check_expand_helper_final(final_expanded, i, data);
	return (final_expanded);
}

/*============================================================================*/