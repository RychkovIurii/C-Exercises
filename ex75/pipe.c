/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:17:41 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/13 11:02:03 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	// random => random * 4 = 20 => 20
	int	pipefd1[2]; //Child => Parent
	int	pipefd2[2]; //Parent => Child

	if (pipe(pipefd1) == -1)
		return (1);
	if (pipe(pipefd2) == -1)
		return (1);

	int	pid;
	pid = fork();
	if (pid == -1)
		return (1);

	if (pid == 0)
	{
		//Child proccess
		close(pipefd1[0]); //we only write to this pipefd
		close(pipefd2[1]); //we only read from this pipefd
		int	x;
		if (read(pipefd2[0], &x, sizeof(x)) == -1)
			return (1);
		printf("Recieved %d\n", x);
		x = x * 4;
		if (write(pipefd1[1], &x, sizeof(x)) == -1)
			return (1);
		printf("Wrote %d\n", x);
		close(pipefd2[0]);
		close(pipefd1[1]);
	}
	else
	{
		//Parent proccess
		close(pipefd2[0]); //we only write to this pipefd
		close(pipefd1[1]); //we only read from this pipefd
		srand(time(NULL));
		int	y;
		y = rand() % 10;
		if (write(pipefd2[1], &y, sizeof(y)) == -1)
			return (1);
		printf("Wrote %d\n", y);
		if (read(pipefd1[0], &y, sizeof(y)) == -1)
			return (1);
		printf("Result %d\n", y);
		close(pipefd1[0]);
		close(pipefd2[1]);
		wait(NULL);
	}

	return (0);
}
