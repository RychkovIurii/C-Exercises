/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_args_to_threads2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:43:47 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/06 15:49:17 by irychkov         ###   ########.fr       */
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
	int	num = *(int *)arg;
	printf("Number is {%d}\n", num);
}

int	main(int ac, char *av[])
{
	int			i;
	pthread_t	th[10];

	i = 0;
	while (i < 10)
	{
		if (pthread_create(&th[i], NULL, &print_one, &array[i]) != 0)
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
 % ./pass_args_to_threads2
Number is {3}
Number is {24}
Number is {19}
Number is {27}
Number is {23}
Number is {11}
Number is {2}
Number is {7}
Number is {29}
Number is {5}

 */