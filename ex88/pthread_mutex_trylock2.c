/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_mutex_trylock2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:24:55 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/07 11:42:15 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

//Example with several stoves

// chef = threads
// stove = shared data (+mutex)

pthread_mutex_t	stove_mutex[4];
int	stove_gas[4] = { 100, 100, 100, 100 };

void	*routine(void *arg)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (pthread_mutex_trylock(&stove_mutex[i]) == 0)
		{
			int gas_needed = (rand() % 40);
			if (stove_gas[i] - gas_needed < 0)
				printf("No more gas. Going home\n");
			else
			{
				stove_gas[i] -= gas_needed;
				usleep(500000);
				printf("Gas left %d\n", stove_gas[i]);
			}
			pthread_mutex_unlock(&stove_mutex[i]);
			break ;
		}
		else
		{
			if (i == 3)
			{
				printf("Chef is waiting a stove\n");
				usleep(300000);
				i = 0;
			}
		}
		i++;
	}
}

int	main(int ac, char *av[])
{
	int			i;
	int			j;
	pthread_t	th[10];

	i = 0;
	j = 0;
	srand(time(NULL));
	while(j < 4)
	{
		pthread_mutex_init(&stove_mutex[j], NULL);
		j++;
	}
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
	j = 0;
	while(j < 4)
	{
		pthread_mutex_destroy(&stove_mutex[j]);
		j++;
	}
	return (0);
}
