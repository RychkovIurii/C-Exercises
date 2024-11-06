/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_args_to_threads3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:51:27 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/06 17:22:06 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//sum args of array with two treads

int	array[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void	*routine(void *arg)
{
	int	i;
	int	index;
	int	sum;

	i = 0;
	sum = 0;
	index = *(int *)arg;
	while(i < 5)
	{
		sum += array[index++];
		i++;
	}
	printf("Sum is {%d}\n", sum);
	*(int *)arg = sum;
	return (arg);
}

int	main(int ac, char *av[])
{
	int			i;
	int			*a;
	int			sum;
	pthread_t	th[2];

	i = 0;
	sum = 0;
	while (i < 2)
	{
		a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
		{
		perror("pthread_create failed");
		return (1);
		}
		i++;
	}
	i = 0;
	while (i < 2)
	{
		int *middle_result;
		if (pthread_join(th[i], (void *)&middle_result) != 0)
		{
			perror("pthread_join failed");
			return (1);
		}
		sum += *middle_result;
		free(middle_result);
		i++;
	}
	printf("Sum of two threads is {%d}", sum);
	return (0);
}
