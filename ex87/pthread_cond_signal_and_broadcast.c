/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_cond_signal_and_broadcast.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:39:10 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/07 11:02:49 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// HUOM! pthread_cond_signal signals only to one thread

pthread_mutex_t	mutex_fuel;
pthread_cond_t	cond_fuel;
int	fuel = 0;

void*	fuel_filling(void* arg)
{
	int	i;

	i = 0;
	while (i < 11)
	{
		pthread_mutex_lock(&mutex_fuel);
		fuel += 15;
		printf("Filled fuel... %d\n", fuel);
		pthread_mutex_unlock(&mutex_fuel);
		pthread_cond_broadcast(&cond_fuel);
		sleep(1);
		i++;
	}
}

void*	car(void* arg)
{
	pthread_mutex_lock(&mutex_fuel);
	while (fuel < 40)
	{
		printf("No fuel. Waiting...\n");
		pthread_cond_wait(&cond_fuel, &mutex_fuel);
		// Equivalent to:
		// pthread_mutex_unlock(&mutex_fuel);
		// wait for signal on cond_fuel
		// pthread_mutex_lock(&mutex_fuel);
	}
	fuel -= 40;
	printf("Got fuel. Now left: %d\n", fuel);
	pthread_mutex_unlock(&mutex_fuel);
}

int main(int argc, char* argv[])
{
	int			i;
	pthread_t	th[6];

	i = 0;
	pthread_mutex_init(&mutex_fuel, NULL);
	pthread_cond_init(&cond_fuel, NULL);
	while (i < 6)
	{
		if (i == 4 || i == 5)
		{
			if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0)
				perror("Failed to create thread");
		}
		else
		{
			if (pthread_create(&th[i], NULL, &car, NULL) != 0)
				perror("Failed to create thread");
		}
		i++;
	}
	i = 0;
	while (i < 6)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
	pthread_mutex_destroy(&mutex_fuel);
	pthread_cond_destroy(&cond_fuel);
	return 0;
}

//cc pthread_cond_signal_and_broadcast.c -o pthread_cond_signal_and_broadcast -lpthread