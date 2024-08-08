/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:47:48 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/08 13:52:46 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

/* We got an array from fifo4 and calculated a sum */

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
	if(read(fd, arr, sizeof(int) * 5) == -1)
	{
	perror("read");
	return 1;
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
