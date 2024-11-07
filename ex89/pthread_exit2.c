/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_exit2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:53:56 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/07 13:04:41 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

//Example how we can return a value from the thread

void	*roll_dice()
{
	int	value;
	int	*result;

	value = (rand() % 6) + 1;
	result = malloc(sizeof(int));
	*result = value;
	printf("Thread result is {%d}\n", value);
	pthread_exit((void *)result);
}

int	main(int ac, char *av[])
{
	int	*result;
	pthread_t	th;

	srand(time(NULL));
	if(pthread_create(&th, NULL, &roll_dice, NULL) != 0)
	{
		perror("pthread_create failed");
		return (1);
	}
	pthread_exit (0);	// If we use exit(0) we won't see result from thread. It terminates the process.
						// But if we use pthread_exit it won't terminate the process and we see the result (Thread result is {2}).
						// BTW we have a memory leak.
	if (pthread_join(th, (void **)&result) != 0)
	{
		perror("pthread_join failed");
		return (1);
	}
	printf("Result is {%d}\n", *result);
	free(result);
	return (0);
}
