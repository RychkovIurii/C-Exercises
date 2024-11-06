/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trylock_and_lock.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:45:17 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/06 20:13:38 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t	mutex;

void	*routine(void *arg)
{
	if (pthread_mutex_trylock(&mutex) == 0)
	{
		printf("Got the lock\n");
		sleep(1);
		pthread_mutex_unlock(&mutex);
	}
	else
		printf("Failed to get the lock\n");
	/* pthread_mutex_lock(&mutex);
	printf("Got the lock\n");
	sleep(1);
	pthread_mutex_unlock(&mutex); */
}

int	main(int ac, char *av[])
{
	int			i;
	pthread_t	th[4];

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < 4)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
		perror("pthread_create failed");
		return (1);
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("pthread_join failed");
			return (1);
		}
		i++;
	}
	return (0);
}

//cc trylock_and_lock.c -o trylock_and_lock -lpthread

/*
./trylock_and_lock
Got the lock
Failed to get the lock
Failed to get the lock
Failed to get the lock

./trylock_and_lock
Got the lock
Got the lock
Got the lock
Got the lock
 */
