/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_initializer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:33:08 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/10 19:17:32 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#define THREAD_NUM 2

pthread_mutex_t	mutex_fuel = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t	cond_fuel = PTHREAD_COND_INITIALIZER;

void	*routine(void *arg)
{

}

int	main(int ac, char *av[])
{
	int			i;
	pthread_t	th[THREAD_NUM];

	i = 0;
	/* pthread_mutex_init(&mutex_fuel, NULL); */
	while (i < THREAD_NUM)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
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
	/* pthread_mutex_destroy(&mutex_fuel); */
	return (0);
}
