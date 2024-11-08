/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_t.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:08:46 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/08 11:59:56 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>

#define THREAD_NUM 2

void	*routine(void *arg)
{
	pthread_t th = pthread_self();
	printf("%lu is identifier from routine pthread\n", th);
	// !process id and thread id are different
	printf("%d is from gettid\n", (pid_t) syscall(SYS_gettid));
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
		printf("%lu is identifier for pthread\n", th[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_NUM)
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
