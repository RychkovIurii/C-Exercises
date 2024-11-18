/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:46:26 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/18 12:53:48 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 16

sem_t semaphore;

void	*routine(void *arg)
{
	printf("ID {%d} is waiting in the queue\n", *(int *)arg);
	sem_wait(&semaphore);
	printf("ID {%d} logged in\n", *(int *)arg);
	sleep(3);
	printf("\t\tID {%d} logged OUT\n", *(int *)arg);
	sem_post(&semaphore);
	free(arg);
}

int	main(int ac, char *av[])
{
	int			i;
	pthread_t	th[THREAD_NUM];

	i = 0;
	sem_init(&semaphore, 0, 12);
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
