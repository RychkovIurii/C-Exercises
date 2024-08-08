/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:49:03 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/08 12:31:25 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

/* Opening the read or write end of a FIFO blocks until the other end is
also opened (by another process  or  thread). USE CAT if you wanna finish the execution. Or you can switch to open("myfifo1", O_RDWR)*/
/* We can create fifofile from command line as well (% mkfifo myfifo1) */


int	main(int argc, char *argv[])
{
	if (mkfifo("myfifo1", 0777) == -1)
	{
		printf("Couldn't create the fifo file\n");
		return (1);
	}

	printf("Opening...\n");
	int	fd;
	fd = open("myfifo1", O_WRONLY);
	if (fd == -1)
	{
		perror("open");
		return 1;
	}
	printf("Opened\n");
	int	x = 97;
	if (write(fd, &x, sizeof(x)) == -1) // Will print 'A' (ASCII 97)
	{
		perror("write");
		return 1;
	}
	printf("Written\n");
	close(fd);
	printf("Closed\n");

	return (0);
}

/* int	main(int argc, char *argv[])
{
	if (mkfifo("myfifo1", 0777) == -1)
	{
		if (errno != EEXIST)
		{
			printf("Couldn't create the fifo file\n");
			return (1);
		}
		return (1);
	}
	return (0);
} */