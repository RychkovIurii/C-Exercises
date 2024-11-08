/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_detach2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:16:09 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/08 12:28:43 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#define THREAD_NUM 2

void	*routine(void *arg)
{
	sleep(1);
	printf("Finished the execution\n");
}

int	main(int ac, char *av[])
{
	int				i;
	pthread_t		th[THREAD_NUM];
	pthread_attr_t	detached_thread;

	i = 0;
	pthread_attr_init(&detached_thread);
	pthread_attr_setdetachstate(&detached_thread, PTHREAD_CREATE_DETACHED);
	while (i < THREAD_NUM)
	{
		if (pthread_create(&th[i], &detached_thread, &routine, NULL) != 0)
		{
		perror("pthread_create failed");
		}
		//pthread_detach(th[i]);
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
	pthread_attr_destroy(&detached_thread);
	// return (0); it won't wait threads 
	//and will finish the execution before we'll get messages from routine funct
	pthread_exit(0);
}
