/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:48:05 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/08 13:47:08 by irychkov         ###   ########.fr       */
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
We compile both files and run. We pass the array from fifo2 
to fifo3.*/


int	main(int argc, char *argv[])
{
	int	arr[5];
	srand(time(NULL));
	int	i;
	i = 0;
	while (i < 5)
	{
		arr[i] = rand() % 100;
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
	while (i < 5)
	{
		if (write(fd, &arr[i], sizeof(int)) == -1)
		{
		perror("write");
		return 1;
		}
		printf("Wrote %d\n", arr[i]);
		i++;
	}
	if (close(fd))
		return (1);
	return (0);
}