/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_self.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:10:48 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/06 12:09:04 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void	*print_hello(void * data)
{
	int	my_data;
	pthread_t tid;

	my_data = *(int *)data;
	tid = pthread_self();
	printf("\nHello from new thread %lu - got %d !\n", (long unsigned int)tid, my_data);
	pthread_exit(NULL);
}

int	main(void)
{
	int			t;
	int			rc;
	pthread_t	thread_id;
	pthread_t	tid;

	t = 11;
	tid = pthread_self();
	printf("I am thread %u. ", (unsigned)tid);
	rc = pthread_create(&thread_id, NULL, print_hello, (void*)&t);
	if(rc)
	{
		printf("\nERROR: return code from pthread_create is %d \n", rc);
		exit(1);
	}
	printf("\nCreated new thread (%lu)... \n", thread_id);
	pthread_exit(NULL);
	return (0);
}

//cc pthread_self.c -o pthread_self -lpthread