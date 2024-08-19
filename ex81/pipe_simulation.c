/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:05:23 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/19 10:47:33 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
# include <fcntl.h>

/* pipe_simulation2 is more typical of Unix pipeline patterns,
where each part of the pipeline is handled by a separate process.
This is just example! */

int	main(int argc, char *argv[])
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		return (1);
		
	pid = fork();
	if (pid == -1)
		return (1);
	
	if (pid == 0)
	{
		//Child proccess 1 (ping)

		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 failed for STDOUT");
			return 1;
		}
		close(fd[0]);
		close(fd[1]);
		if (execlp("ping", "ping", "-c", "3", "google.com", NULL) == -1)
		{
			perror("execlp failed");
			return (1);
		}
	}
	else
	{
		//Parent proccess
		int	waitstatus;

		wait(&waitstatus);
		if (WIFEXITED(waitstatus))
		{
			int	status_code;

			status_code = WEXITSTATUS(waitstatus);
			if (status_code == 0)
			{
				if (dup2(fd[0], STDIN_FILENO) == -1)
				{
					perror("dup2 failed for STDIN");
					return 1;
				}
				close(fd[0]);
				close(fd[1]);
				if (execlp("grep", "grep", "round-trip", NULL) == -1)
				{
					perror("execlp failed");
					return (1);
				}
			}
			else
				printf("Child proccess Failure with status_code %d!\n", status_code);
		}
		printf("Some post processing goes here!\n");
	}
	return (0);
}