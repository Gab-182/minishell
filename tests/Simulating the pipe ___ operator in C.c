/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Simulating the pipe ___ operator in C.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 08:13:06 by gabdoush          #+#    #+#             */
/*   Updated: 2022/06/29 10:52:22 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/**
 * @file Simulating the pipe "|" operator in C.c
 * @brief program to implement a pipe between two proccess.
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(void)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	/*--------------------------------------------------------------*/
	if (pipe(fd) == -1)
	{
		perror("Error at pipe");
		return (1);
	}
	/*--------------------------------------------------------------*/
	// First proccess [ping -c 5 google.com]
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("Error at forking pid1");
		return (2);
	}
	if (pid1 == 0)
	{
		// Child proccess 1 (ping).
		dup2(fd[1], STDOUT_FILENO);
		// Close the fds for the first proccess.
		close(fd[1]);
		close(fd[0]);
		// ping going to write to stdout
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	/*--------------------------------------------------------------*/
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("Error at forking pid2");
		return (3);
	} 
	if (pid2 == 0)
	{
		//Child proccess 2 (grep)
		dup2(fd[0], STDIN_FILENO);
		// Close the fds for the second proccess.
		close(fd[0]);
		close(fd[1]);
		// grep which going to read from stdin
		execlp("grep", "grep", "trip", NULL);
	}
	/*--------------------------------------------------------------*/
	// Close the fds for the main proccess, 
	// Cause we have basically 3 proccess each one of them has 2 fd open (in, out)
	// including the main proccess.
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}