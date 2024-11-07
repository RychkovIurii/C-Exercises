/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_barrier2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:47:21 by irychkov          #+#    #+#             */
/*   Updated: 2024/11/07 17:55:14 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// Problem: Every thread rolls a dice, saved its value in an array.
// The main thread calculates the winner then
// each thread prints a message with whether or not they lost or won.

#define THREAD_NUM 8

int	dice_values[8];
int	status[8] = { 0 };

pthread_barrier_t barrier_check;
pthread_barrier_t barrier_calculated;

void	*roll_dice(void *args)
{
	int	index = *(int *)args;
	dice_values[index] = rand() % 6 + 1;
	pthread_barrier_wait(&barrier_check);
	pthread_barrier_wait(&barrier_calculated);
	if (status[index] == 1)
	{
		printf("(%d rolled %d) I won\n", index, dice_values[index]);
	}
	else
	{
		printf("(%d rolled %d) I lost\n", index, dice_values[index]);
	}
	free(args);
}

int	main(int ac, char *av[])
{
	int			i;
	int			max;
	int			*a;
	pthread_t	th[THREAD_NUM];
	pthread_barrier_init(&barrier_check, NULL, THREAD_NUM + 1);
	pthread_barrier_init(&barrier_calculated, NULL, THREAD_NUM + 1);

	max = 0;
	i = 0;
	srand(time(NULL));
	while (i < THREAD_NUM)
	{
		a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &roll_dice, a) != 0)
		{
		perror("pthread_create failed");
		return (1);
		}
		i++;
	}
	pthread_barrier_wait(&barrier_check);
	i = 0;
	while (i < THREAD_NUM)
	{
		if (dice_values[i] > max)
			max = dice_values[i];
		i++;
	}
	i = 0;
	while (i < THREAD_NUM)
	{
		if (dice_values[i] == max)
			status[i] = 1;
		else
			status[i] = 0;
		i++;
	}
	pthread_barrier_wait(&barrier_calculated);
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
	pthread_barrier_destroy(&barrier_check);
	pthread_barrier_destroy(&barrier_calculated);
	return (0);
}

/* void	*roll_dice(void *args)
{
	int	index = *(int *)args;
	dice_values[index] = rand() % 6 + 1;
	pthread_barrier_wait(&barrier_check);
	pthread_barrier_wait(&barrier_calculated);
	if (status[index] == 1)
	{
		printf("(%d rolled %d) I won\n", index, dice_values[index]);
	}
	else
	{
		printf("(%d rolled %d) I lost\n", index, dice_values[index]);
	}
	free(args);
}

int	main(int ac, char *av[])
{
	int			i;
	int			max;
	int			*a;
	pthread_t	th[THREAD_NUM];
	pthread_barrier_init(&barrier_check, NULL, THREAD_NUM + 1);
	pthread_barrier_init(&barrier_calculated, NULL, THREAD_NUM + 1);

	max = 0;
	i = 0;
	srand(time(NULL));
	while (i < THREAD_NUM)
	{
		a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &roll_dice, a) != 0)
		{
		perror("pthread_create failed");
		return (1);
		}
		i++;
	}
	while (1)
	{
		pthread_barrier_wait(&barrier_check);
		i = 0;
		while (i < THREAD_NUM)
		{
			if (dice_values[i] > max)
				max = dice_values[i];
			i++;
		}
		i = 0;
		while (i < THREAD_NUM)
		{
			if (dice_values[i] == max)
				status[i] = 1;
			else
				status[i] = 0;
			i++;
		}
		printf("\n===== New ROUND =====\n");
		sleep(1);
		pthread_barrier_wait(&barrier_calculated);
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
	pthread_barrier_destroy(&barrier_check);
	pthread_barrier_destroy(&barrier_calculated);
	return (0);
} */