/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_mutexes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:46:55 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/18 11:50:24 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_NUM 6

pthread_mutex_t	mutexFuel;
int				fuel = 50;

void	*routine(void* args)
{
	pthread_mutex_lock(&mutexFuel);
	pthread_mutex_lock(&mutexFuel);
	pthread_mutex_lock(&mutexFuel);
	pthread_mutex_lock(&mutexFuel);
	fuel += 50;
	printf("Incremented fuel to %d\n", fuel);
	pthread_mutex_unlock(&mutexFuel);
	pthread_mutex_unlock(&mutexFuel);
	pthread_mutex_unlock(&mutexFuel);
	pthread_mutex_unlock(&mutexFuel);
}

int	main(int argc, char *argv[])
{
	pthread_t			th[THREAD_NUM];
	pthread_mutexattr_t	recursiveMutexAttributes;

	pthread_mutexattr_init(&recursiveMutexAttributes);
	pthread_mutexattr_settype(&recursiveMutexAttributes, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&mutexFuel, &recursiveMutexAttributes);

	int i;
	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("Failed to create thread");
		}
	}

	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to join thread");
		}
	}
	printf("Fuel: %d\n", fuel);
	pthread_mutexattr_destroy(&recursiveMutexAttributes);
	pthread_mutex_destroy(&mutexFuel);
	return (0);
}