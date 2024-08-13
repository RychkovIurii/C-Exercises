/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:20:45 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/13 11:38:10 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

/* int	main(int argc, char *argv[])
{
	execlp("ping", "ping", "-c", "3", "google.com", NULL);
	printf("Success!"); //we won't see it. Exec func replaces all processes
	return (0);
} */

int	main(int argc, char *argv[])
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	
	if (pid == 0)
	{
		//Child proccess
		//execlp("mkfifo", "mkfifo", "sum", NULL);
		execlp("ping", "ping", "-c", "3", "google.com", NULL);
	}
	else
	{
		//Parent proccess
		wait(NULL);
		printf("Some post processing goes here!\n");
	}

	printf("Success!\n");
	return (0);
}