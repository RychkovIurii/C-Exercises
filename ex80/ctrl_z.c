/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_z.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:55:51 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/16 16:33:37 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, char *argv[])
{
	int	x;

	printf("Input a number: ");
	scanf("%d", &x);
	printf("Result: %d * 5 = %d\n", x, x * 5);
	return (0);
}
// from terminal we can stop the process by pressing ctrl + z (SIGTSTP)
// from terminal we can resume the process by typing fg (SIGCONT) or fg <job number>

/* Be cautious with signals, as the behavior of zsh and bash shells can differ.
In my case on macOS, when I resumed the process using 'fg',
the program unexpectedly received the value 1. */