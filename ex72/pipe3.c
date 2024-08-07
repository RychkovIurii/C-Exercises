/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:14:19 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/07 16:37:07 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Practical use case for fork and pipe in C
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int	main(int argc, char *argv[])
{
	int		start, end;
	int		arr[] = { 1, 2, 3, 4, 1, 2 };
	int		size_arr;
	int		pipefd[2];
	pid_t	pid;

	size_arr = sizeof(arr) / sizeof(int);

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return 1;
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return 1;
	}
	if (pid == 0)
	{
		start = 0;
		end = size_arr / 2;
	}
	else
	{
		start = size_arr / 2;
		end = size_arr;
	}

	int	sum;
	int	i;

	sum = 0;
	i = start;
	while (i < end)
	{
		sum = sum + arr[i];
		i++;
	}

	printf("Calculated partial sum: %d\n", sum);

	if (pid == 0)
	{
		close(pipefd[0]);

		if (write(pipefd[1], &sum, sizeof(sum)))
			return (2); //Error validation
		close(pipefd[1]);
	}
	else
	{
		close(pipefd[1]);

		int	sum_from_child;
		if (read(pipefd[0], &sum_from_child, sizeof(sum_from_child)) == -1)
			return (2); //Error validation
		close(pipefd[0]);

		int	total;
		total = sum + sum_from_child;
		printf("Total sum is %d\n", total);
		wait(NULL);
	}

	return (0);
}