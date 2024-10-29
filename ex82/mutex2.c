/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:10:47 by irychkov          #+#    #+#             */
/*   Updated: 2024/10/29 12:15:58 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int	mails = 0;
pthread_mutex_t	mutex;

void	*routine()
{
	for (int i = 0; i < 10000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		// read mails
		// increment mails
		// write mails
	}
}

int	main(int ac, char *av[])
{
	pthread_t	p1;
	pthread_t	p2;
	pthread_t	p3;
	pthread_t	p4;

	pthread_mutex_init(&mutex, NULL);
	if(pthread_create(&p1, NULL, routine, NULL) != 0)
	{
		perror("pthread_create failed");
		return (1);
	}
	if(pthread_create(&p2, NULL, routine, NULL) != 0)
	{
		perror("pthread_create failed");
		return (1);
	}
	if(pthread_create(&p3, NULL, routine, NULL) != 0)
	{
		perror("pthread_create failed");
		return (1);
	}
	if(pthread_create(&p4, NULL, routine, NULL) != 0)
	{
		perror("pthread_create failed");
		return (1);
	}
	if (pthread_join(p1, NULL) != 0)
	{
		perror("pthread_join failed");
		return (1);
	}
	if (pthread_join(p2, NULL) != 0)
	{
		perror("pthread_join failed");
		return (1);
	}
	if (pthread_join(p3, NULL) != 0)
	{
		perror("pthread_join failed");
		return (1);
	}
	if (pthread_join(p4, NULL) != 0)
	{
		perror("pthread_join failed");
		return (1);
	}
	pthread_mutex_destroy(&mutex);
	printf("mails: %d\n", mails);
	return (0);
}
