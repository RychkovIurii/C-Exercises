/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:49:25 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/07 13:58:03 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

int	main(void)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork1");
		return 1;
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("fork2");
		return 1;
	}

	if (pid1 == 0)
	{
		if(pid2 == 0)
			printf("We are process y\n");
		else
			printf("We are process x\n");
	}
	else
	{
		if(pid2 == 0)
			printf("We are process z\n");
		else
			printf("We are the parent process\n");
	}

	while(wait(NULL) != -1 || errno != ECHILD)
		printf("Waited for a child to finish\n");
	return 0;
}