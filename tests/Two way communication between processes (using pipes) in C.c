/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Two way communication between processes (us        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:58:55 by gabdoush          #+#    #+#             */
/*   Updated: 2022/07/03 13:35:36 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
/*--------------------------------------------------------------*/
/**
 * @brief communicate between two proccess using pipes,
 * reading and writing from and to the two proccess
 * 
 * 1- #Define a number in the main proccess.
 * 2- #Let a child proccess read that value, then do (* 5) to the value.
 * 3- #then let the main proccess read that value.
 */
/*--------------------------------------------------------------*/
int	main(void)
{
	int	p1[2]; // C -> P [child to parent]
	int	p2[2]; // P -> C [parent to child]

	pipe(p1);
	pipe(p2);
	int	pid = fork();
	if (pid == -1)
	{
		perror("failed to fork a proccess");
		return (1);
	}
	// Child process.
	if (pid == 0)
	{
		int	x;
		close(p2[1]);
		close(p1[0]);

		read(p2[0], &x, sizeof(x));
		printf("The child has read [%d]\n", x);

		x = x * 4;

		write(p1[1], &x, sizeof(x));

		printf("The child write [%d] to the parent\n", x);
		close(p2[0]);
		close(p1[1]);
	}
	// Parent proccess.
	else
	{
		int	y;
		y = 5;
		close(p1[1]);
		close(p2[0]);

		write(p2[1], &y, sizeof(y));
		printf("The parent write [%d] to the child\n", y);

		read(p1[0], &y, sizeof(y));
		printf("The parent has read [%d]\n", y);

		close(p2[0]);
		close(p1[1]);
		wait(NULL);
	}
	return (0);
}
/*--------------------------------------------------------------*/