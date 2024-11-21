/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_of_semaphore.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:17:09 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/21 16:28:13 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define THREAD_NUM 4

sem_t	semaphore;

void*	routine(void* args) 
{
	int index = *(int*)args;
	int semaphore_value;

	sem_wait(&semaphore);
	sleep(index + 1);
	sem_getvalue(&semaphore, &semaphore_value); //might be a reason of race condition
	printf("(%d) Current semaphore value after wait is %d\n", index, semaphore_value);
	sem_post(&semaphore);
	sem_getvalue(&semaphore, &semaphore_value);
	printf("(%d) Current semaphore value after post is %d\n", index, semaphore_value);
	free(args);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int	i;
	pthread_t th[THREAD_NUM];

	sem_init(&semaphore, 0, 4);
	i = 0;
	while (i < THREAD_NUM)
	{
		int* a = malloc(sizeof(int));
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

/* 
 % ./value_of_semaphore 
(0) Current semaphore value after wait is 0
(0) Current semaphore value after post is 1
(1) Current semaphore value after wait is 1
(1) Current semaphore value after post is 2
(2) Current semaphore value after wait is 2
(2) Current semaphore value after post is 3
(3) Current semaphore value after wait is 3
(3) Current semaphore value after post is 4
 */