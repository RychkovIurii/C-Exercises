/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:00:16 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/15 17:22:43 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
# include <signal.h>

int	main(int argc, char *argv[])
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	
	if (pid == 0)
	{
		//Child proccess
		while (1)
		{
			printf("The child process is running\n");
			usleep(50000); //50 milliseconds
		}
	}
	else
	{
		//Parent proccess
		sleep(1);
		kill(pid, SIGKILL);
		int	waitstatus;

		wait(&waitstatus);
		if (WIFEXITED(waitstatus))
		{
			printf("The child process exited with status %d\n", WEXITSTATUS(waitstatus));
		}
		else if (WIFSIGNALED(waitstatus))
		{
			printf("The child process was killed by signal %d\n", WTERMSIG(waitstatus));
		}
/* 		// Check if the child process was stopped by a signal
		else if (WIFSTOPPED(waitstatus))
		{
			printf("The child process was stopped by signal %d\n", WSTOPSIG(waitstatus));
		}
		// Check if the child process was resumed after being stopped
		#ifdef WIFCONTINUED
		else if (WIFCONTINUED(waitstatus))
		{
			printf("The child process was resumed by SIGCONT\n");
		}
		#endif */
	}
	return (0);
}