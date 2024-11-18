/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:58:41 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/18 12:40:50 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 4

sem_t semaphore;

void	*routine(void *arg)
{
	sem_wait(&semaphore);
	sleep(1);
	printf("Hello from thread %d\n",*(int *)arg);
	sem_post(&semaphore);
	free(arg);
}

int	main(int ac, char *av[])
{
	int			i;
	pthread_t	th[THREAD_NUM];

	i = 0;
	sem_init(&semaphore, 0, 2); // key diff if we launch sem_init(&semaphore, 0, 1)
	//it works as mutex. With value 2 it allows 2 threads pass through
	while (i < THREAD_NUM)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
		{
			perror("pthread_create failed");
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
	sem_destroy(&semaphore);
	return (0);
}
