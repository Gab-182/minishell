/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipes_forks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 02:15:35 by gabdoush          #+#    #+#             */
/*   Updated: 2022/07/01 14:27:13 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file test_pipes_forks.c
 * @brief program to divide the sum of (arr) calculation to two proccess
 * # The parent proccess.
 * # A child proccess.
 * @date 2022-06-29
 */


#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(void)
{
	int	arr[] = {1, 5, 4, 3, 2, 1, 5, 6, 3};
	int arr_size = sizeof(arr) / sizeof(int);
	int	start;
	int	end;
	int	fd[2];
	int	id;

	//creating a pipe;
	if (pipe(fd) == -1)
	{
		perror("Creating a pipe failed");
		return (1);
	}
	//Fork a child.
	id = fork();
	if (id == -1)
	{
		perror("Forking failed");
		return (2);
	}
	if (id == 0)
	{
		// Child proccess.
		start = 0;
		end = arr_size / 2;
	}
	else
	{
		// Parent proccess.
		start = arr_size / 2;
		end = arr_size;
	}
	// What should each proccess do.
	int	sum;
	int	i;

	sum = 0;
	i = start;
	while (i < end)
	{
		sum += arr[i];
		i++;
	}
	printf("The sum of the arr elements = [%d]\n", sum);
	// Using the pipes to make the parent read the result of the child
	// and calculate the total sum.
	if (id == 0)
	{
		close(fd[0]);
		write(fd[1], &sum, sizeof(sum));
		close(fd[1]);
	}
	else
	{
		int	sum_from_child;
		int	total_sum;

		close(fd[1]);
		read(fd[0], &sum_from_child, sizeof(sum_from_child));
		close(fd[0]);

		total_sum = sum + sum_from_child;
		printf("The total sum = [%d]\n", total_sum);
		// wait until the child is done.
		wait(NULL);
	}
	return (0);
}