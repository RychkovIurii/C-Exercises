/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:45:25 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/07 12:50:01 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

//Example how we can return a value from the thread

void	*roll_dice()
{
	int	value;
	int	*result;

	value = (rand() % 6) + 1;
	result = malloc(sizeof(int));
	*result = value;
	pthread_exit((void *)result);
}

int	main(int ac, char *av[])
{
	int	*result;
	pthread_t	th;

	srand(time(NULL));
	if(pthread_create(&th, NULL, &roll_dice, NULL) != 0)
	{
		perror("pthread_create failed");
		return (1);
	}
	if (pthread_join(th, (void **)&result) != 0)
	{
		perror("pthread_join failed");
		return (1);
	}
	printf("Result is {%d}\n", *result);
	free(result);
	return (0);
}

// Result is {2}