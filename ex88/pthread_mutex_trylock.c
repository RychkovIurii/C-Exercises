/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_mutex_trylock.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:04:43 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/07 11:24:44 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

//Example with one stove

// chef = threads
// stove = shared data (+mutex)

pthread_mutex_t	stove_mutex;
int	stove_gas = 100;

void	*routine(void *arg)
{
	pthread_mutex_lock(&stove_mutex);
	int gas_needed = (rand() % 40);
	if (stove_gas - gas_needed < 0)
		printf("No more gas. Going home\n");
	else
	{
		stove_gas -= gas_needed;
		usleep(500000);
		printf("Gas left %d\n", stove_gas);
	}
	pthread_mutex_unlock(&stove_mutex);
}

int	main(int ac, char *av[])
{
	int			i;
	pthread_t	th[10];

	i = 0;
	srand(time(NULL));
	pthread_mutex_init(&stove_mutex, NULL);
	while (i < 10)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
		perror("pthread_create failed");
		return (1);
		}
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("pthread_join failed");
			return (1);
		}
		i++;
	}
	pthread_mutex_destroy(&stove_mutex);
	return (0);
}
