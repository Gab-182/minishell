/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Communicating between processes.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 06:14:15 by gabdoush          #+#    #+#             */
/*   Updated: 2022/07/01 08:38:22 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Communicating between processes.c
 * @brief Communicating between processes (using pipes) in C
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(void)
{
	// fd[0]: read from stdin
	// fd[1]: write to stdout
	int	fd[2];
	int	id;
	int	i;
	int	j;

	if (pipe(fd) == -1)
	{
		printf("Failed to create a pipe\n");
		return (1);
	}
	// You should use the fork() after applying the pipe.
	id = fork();
	if (id == -1)
	{
		printf("Failed to fork\n");
		return (2);
	}
	if (id == 0)
	{
		// Close the stdout fd, cause we don't need it
		close(fd[0]);
		printf("Choose a number: ");
		scanf("%d", &i);
		if (write(fd[1], &i, sizeof(i)) == -1)
		{
			perror("Error while writing");
			return (3);
		}
		close(fd[1]);
		// Close the stdin fd, cause we finished
	}
	else
	{
		// Close the stdin fd, cause we don't need it
		close(fd[1]);
		if (read(fd[0], &j, sizeof(int)) == -1)
		{
			perror("Error while reading");
			return (4);
		}
		close(fd[0]);
		// Close the stdout fd, cause we finished
		printf("Got this value from the child: j = [%d]\n", j);
	}
	return (0);
}