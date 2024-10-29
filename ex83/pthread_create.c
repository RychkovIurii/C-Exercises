/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:18:47 by irychkov          #+#    #+#             */
/*   Updated: 2024/10/29 12:34:48 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int	mails = 0;
pthread_mutex_t	mutex;

void	*routine()
{
	for (int i = 0; i < 10000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		// read mails
		// increment mails
		// write mails
	}
}

int	main(int ac, char *av[])
{
	int			i;
	pthread_t	th[4];

	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < 4; i++)
	{
		if(pthread_create(th + i, NULL, routine, NULL) != 0)
		{
			perror("pthread_create failed");
			return (1);
		}
		printf("Thread %d has started\n", i);
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("pthread_join failed");
			return (1);
		}
		printf("Thread %d has finished execution\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("mails: %d\n", mails);
	return (0);
}

/* 
Output:
Thread 0 has started
Thread 0 has finished execution
Thread 1 has started
Thread 1 has finished execution
Thread 2 has started
Thread 2 has finished execution
Thread 3 has started
Thread 3 has finished execution
mails: 40000000

!!! They are not running in parallel
 */