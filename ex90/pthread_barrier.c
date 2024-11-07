/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_barrier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:06:33 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/07 13:48:04 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_barrier_t barrier;

void	*routine(void *arg)
{
	while (1)
	{
		printf("Waiting at the barrier\n"); //threads wait till we have the number in init
		sleep(1);
		pthread_barrier_wait(&barrier);
		printf("Passed\n");
		sleep(1);
	}
	
}

int	main(int ac, char *av[])
{
	int			i;
	pthread_t	th[10];

	i = 0;
	pthread_barrier_init(&barrier, NULL, 7);
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
	pthread_barrier_destroy(&barrier);
	return (0);
}