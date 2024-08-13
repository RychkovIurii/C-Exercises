/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execlp_with_exit_status.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:47:43 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/13 12:05:18 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

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

		//err = execlp("pingu", "ping", "-c", "3", "google.com", NULL);
		err = execlp("ping", "ping", "-c", "3", "google.con", NULL);
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