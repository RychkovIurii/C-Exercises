/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_args_to_threads.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:12:00 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/06 15:48:40 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//each thread prints only one unique prime from the array

int	array[10] = { 2, 3, 5, 7, 11, 24, 27, 19, 23, 29 };

void	*print_one(void *arg)
{
	sleep(1);
	int	index = *(int *)arg;
	printf("Number is {%d}, index is {%d}\n", array[index], index);
	free(arg);
}

int	main(int ac, char *av[])
{
	int			*a;
	int			i;
	pthread_t	th[10];

	i = 0;
	while (i < 10)
	{
		a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &print_one, a) != 0)
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
	return (0);
}

//cc pass_args_to_threads.c -o pass_args_to_threads -lpthread

/*
% ./pass_args_to_threads 
Number is {2}, index is {0}
Number is {3}, index is {1}
Number is {7}, index is {3}
Number is {11}, index is {4}
Number is {5}, index is {2}
Number is {19}, index is {7}
Number is {23}, index is {8}
Number is {29}, index is {9}
Number is {27}, index is {6}
Number is {24}, index is {5}
 */