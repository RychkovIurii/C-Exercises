/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:17:53 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/21 15:14:56 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 8

int	buffer[10];
int	count = 0;

sem_t			semaphore_empty;
sem_t			semaphore_full;
pthread_mutex_t mutex_buffer;

void	*producer(void *arg)
{
	while (1)
	{
		//Produce
		int x = rand() % 100;

		sleep(1);
		//Add to the buffer
		sem_wait(&semaphore_empty);
		pthread_mutex_lock(&mutex_buffer);
		buffer[count] = x;
		count++;
		pthread_mutex_unlock(&mutex_buffer);
		sem_post(&semaphore_full);
	}
}

void	*consumer(void *arg)
{
	while (1)
	{
		//Remove from the bugger
		int y;
		sem_wait(&semaphore_full);
		pthread_mutex_lock(&mutex_buffer); // have to improve. Think
		y = buffer[count -1];
		count--;
		pthread_mutex_unlock(&mutex_buffer);
		sem_post(&semaphore_empty);

		//Consume
		printf("We got %d\n", y);
	}
}

int	main(int ac, char *av[])
{
	srand(time(NULL));
	int			i;
	pthread_t	th[THREAD_NUM];

	i = 0;
	sem_init(&semaphore_empty, 0, 10);
	sem_init(&semaphore_full, 0, 0);
	pthread_mutex_init(&mutex_buffer,NULL);
	while (i < THREAD_NUM)
	{
		if (i == 0)
		{
			if (pthread_create(&th[i], NULL, &producer, NULL) != 0)
			{
				perror("pthread_create failed");
			}
		}
		else
		{
			if (pthread_create(&th[i], NULL, &consumer, NULL) != 0)
			{
				perror("pthread_create failed");
			}
		}
		i++;
	}
	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("pthread_join failed");
		}
		i++;
	}
	sem_destroy(&semaphore_empty);
	sem_destroy(&semaphore_full);
	pthread_mutex_destroy(&mutex_buffer);
	return (0);
}
