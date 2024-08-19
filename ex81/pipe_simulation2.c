/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_simulation2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:08:17 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/19 10:47:39 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
# include <fcntl.h>

int	main(int argc, char *argv[])
{
	int	pid1, pid2;
	int	fd[2];

	if (pipe(fd) == -1)
		return (1);
		
	pid1 = fork();
	if (pid1 == -1)
		return (1);
	
	if (pid1 == 0)
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
	pid2 = fork();
	if (pid2 == -1)
		return (1);

	if (pid2 == 0)
	{
		//Child proccess 2 (grep)

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

	//Parent proccess
	close(fd[0]);
	close(fd[1]);
	int	waitstatus1;
	int	waitstatus2;

	if (waitpid(pid1, &waitstatus1, 0) == -1)
	{
		perror("waitpid for pid1 failed");
		return 1;
	}
	if (WIFEXITED(waitstatus1))
	{
		int	status_code;

		status_code = WEXITSTATUS(waitstatus1);
		if (status_code == 0)
			printf("Child proccess 1 success!\n");
		else
			printf("Child proccess 1 Failure with status_code %d!\n", status_code);
	}
	if (waitpid(pid2, &waitstatus2, 0) == -1)
	{
		perror("waitpid for pid2 failed");
		return 1;
	}
	if (WIFEXITED(waitstatus2))
	{
		int	status_code;

		status_code = WEXITSTATUS(waitstatus2);
		if (status_code == 0)
			printf("Child proccess 2 success!\n");
		else
			printf("Child proccess 2 Failure with status_code %d!\n", status_code);
	}
	return (0);
}
