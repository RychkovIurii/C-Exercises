/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_detach.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:05:09 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/08 12:15:15 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_NUM 2

void	*routine(void *arg)
{
	sleep(1);
	printf("Finished the execution\n");
}

int	main(int ac, char *av[])
{
	int			i;
	pthread_t	th[THREAD_NUM];

	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
		perror("pthread_create failed");
		return (1);
		}
		pthread_detach(th[i]);
		i++;
	}
	/* i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("pthread_join failed");
		}
		i++;
	} */

	// return (0); it won't wait threads 
	//and will finish the execution before we'll get messages from routine funct
	pthread_exit(0);
}
