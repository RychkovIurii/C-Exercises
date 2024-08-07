/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:37:41 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/07 15:53:38 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int	main(int argc, char *argv[])
{
	int		pipefd[2];
	// pipefd[0] - read
	// pipefd[1] - write

	pid_t	pid;

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
		close(pipefd[0]);

		int	x;
		printf("Input a number: ");
		scanf("%d", &x);
		if (write(pipefd[1], &x, sizeof(int)))
			return (2); //Error validation
		close(pipefd[1]);
	}
	else
	{
		close(pipefd[1]);

		int	y;
		if (read(pipefd[0], &y, sizeof(int)) == -1)
			return (2); //Error validation
		close(pipefd[0]);
		printf("Got from child process %d\n", y);
	}

	return (0);
}