/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:05:21 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/08 13:47:09 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

/* We got an array from fifo2 and calculated a sum */

int	main(int argc, char *argv[])
{
	int	arr[5];
	int	fd;

	fd = open("sum", O_RDONLY);
	if ( fd == -1)
	{
		perror("open");
		return 1;
	}

	int	i;
	i = 0;
	while (i < 5)
	{
		if(read(fd, &arr[i], sizeof(int)) == -1)
		{
		perror("read");
		return 1;
		}
		printf("Received %d\n", arr[i]);
		i++;
	}
	if (close(fd))
		return (1);
	
	int	sum;
	sum = 0;
	i = 0;
	while (i < 5)
	{
		sum += arr[i];
		i++;
	}
	printf("Result is %d", sum);
	
	return (0);
}