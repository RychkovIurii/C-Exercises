/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:58:06 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/07 13:08:15 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(void)
{
	pid_t	pid;
	int		res;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return 1;
	}

	if (pid == 0)
	{
		sleep(1);
	}
	printf("Current ID: %d, parent ID %d\n", getpid(), getppid());

	res = wait(NULL);
	if (res == -1)
		printf("No child left behind\n");
	else
		printf("%d finished execution\n", res);

	return 0;
}