/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:48:10 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/08 13:56:11 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

/* We create a fifofile from a command line at the beginning (% mkfifo sum).
We compile both files and run. We pass the array from fifo4 
to fifo5.*/


int	main(int argc, char *argv[])
{
	int	arr[5];
	srand(time(NULL));
	int	i;
	i = 0;
	while (i < 5)
	{
		arr[i] = rand() % 10;
		printf("Generated %d\n", arr[i]);
		i++;
	}

	int	fd;
	fd = open("sum", O_WRONLY);
	if ( fd == -1)
	{
		perror("open");
		return 1;
	}

	i = 0;
	if (write(fd, arr, sizeof(int) * 5) == -1)
	{
	perror("write");
	return 1;
	}

	if (close(fd))
		return (1);
	return (0);
}