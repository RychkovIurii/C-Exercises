/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:12:20 by irychkov          #+#    #+#             */
/*   Updated: 2024/10/29 13:26:23 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void	*roll_dice()
{
	int	value;

	value = (rand() % 6) + 1;
	printf("%d\n", value);
}

int	main(int ac, char *av[])
{
	pthread_t	th;

	srand(time(NULL));
	if(pthread_create(&th, NULL, &roll_dice, NULL) != 0)
	{
		perror("pthread_create failed");
		return (1);
	}
	if (pthread_join(th, NULL) != 0)
	{
		perror("pthread_join failed");
		return (1);
	}
	return (0);
}
