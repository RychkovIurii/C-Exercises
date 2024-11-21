/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_semaphore2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:30:12 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/21 15:39:26 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define THREAD_NUM 1

sem_t semFuel;

int	*fuel;

void*	routine(void* args)
{
	*fuel += 50;
	printf("Current value is %d\n", *fuel);
	sem_post(&semFuel);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int	i;
	pthread_t th[THREAD_NUM];

	fuel = malloc(sizeof(int));
	*fuel = 50;
	sem_init(&semFuel, 0, 0);
	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("pthread_create failed");
		}
		i++;
	}
	sem_wait(&semFuel);
	printf("Deallocating fuel\n");
	free(fuel);
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
