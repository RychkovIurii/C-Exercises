/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_semaphore3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:03:37 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/21 16:12:26 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define THREAD_NUM 8

// !!!With semaphore we can open semaphore in one thread and close in another one. With mutex we can get undefined behavior.

sem_t semFuel;
int	fuel;

void*	routine1(void* args)
{
	sem_wait(&semFuel);
	fuel += 50;
	printf("Current value is %d\n", fuel);
	return (NULL);
}

void*	routine2(void* args)
{
	sem_post(&semFuel);
	usleep(50000); //works even without usleep
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int	i;
	pthread_t th[THREAD_NUM];

	fuel = 50;
	sem_init(&semFuel, 0, 1);
	i = 0;
	while (i < THREAD_NUM)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&th[i], NULL, &routine1, NULL) != 0)
			{
				perror("pthread_create failed");
			}
		}
		else
		{
			if (pthread_create(&th[i], NULL, &routine2, NULL) != 0)
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
	sem_destroy(&semFuel);
	return (0);
}
