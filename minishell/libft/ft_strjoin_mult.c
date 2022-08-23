/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_mult.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:56:09 by gabdoush          #+#    #+#             */
/*   Updated: 2022/07/07 10:03:58 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*============================================================================*/
/**
 * @brief Edited version of ft_strjoin() to join multiple strings together
 * 
 * @param str_num the number of the strings
 * @param ... the variadic strings
 * @return char*
 **=========================================================================**
 */
char	*ft_strjoin_mult(int str_num, ...)
{
	va_list	args;
	char	*str;
	char	*temp;
	char	*joined_str;

	joined_str = ft_strdup("");
	va_start(args, str_num);
	str = va_arg(args, char *);
	while (str_num > 0)
	{
		temp = joined_str;
		joined_str = ft_strjoin(joined_str, str);
		if (temp)
		{
			free(temp);
			temp = NULL;
		}
		str = va_arg(args, char *);
		str_num--;
	}
	va_end(args);
	return (joined_str);
}

/*============================================================================*/