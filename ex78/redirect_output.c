/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:15:27 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/15 14:00:02 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
# include <fcntl.h>

int	main(int argc, char *argv[])
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	
	if (pid == 0)
	{
		//Child proccess
		int	err;
		int	file;
		int	file2;

		file = open("pingResults.txt", O_WRONLY | O_CREAT, 0777);
		if (file == -1)
		{
			printf("Couldn't open the pingResults.txt\n");
			return (1);
		}

		printf("The fd to pingResults.txt : %d\n", file);
		file2 = dup2(file, STDOUT_FILENO); // We should validate returning value of dup2
		printf("The duplicated fd: %d\n", file2);
		close(file);

		err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
		if (err == -1)
		{
			printf("Couldn't find the program to execute\n");
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
				printf("Child proccess success!\n");
			else
				printf("Child proccess Failure with status_code %d!\n", status_code);
		}
		printf("Some post processing goes here!\n");
	}

	printf("Success!\n");
	return (0);
}