/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:43:52 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/06 14:03:21 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	pid_t	pid;
	int		n;
	int		i;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return 1;
	}

	if (pid == 0)
	{
		printf("it's a child process with PID %d\n", pid);
		n = 1;
	}
	else
	{	
		/* pid = fork();
		printf("it's a parent process with PID %d, child PID %d\n", getpid(), pid); */
		wait();
		n = 6;
	}

	if (pid != 0)
		wait();


	for (i = n; i < n + 5; i++)
	{
		printf("%d ", i);
		fflush(stdout);
	}
	if (pid != 0)
		printf("\n");

	return 0;
}