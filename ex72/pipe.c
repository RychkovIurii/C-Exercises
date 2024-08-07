/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:03:49 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/07 11:09:33 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 256

int	main()
{
	int		pipefd[2];
	pid_t	pid;
	char	write_msg[] = "Hello, this is a longer message that we don't know the size of!";
	char	*read_msg = NULL;
	ssize_t	bytes_read;
	size_t	total_size = 0;
	size_t	current_size = INITIAL_SIZE;

	// Allocate initial buffer
	read_msg = malloc(current_size);
	if (read_msg == NULL)
	{
		perror("malloc");
		return 1;
	}

	// Create the pipe
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		free(read_msg);
		return 1;
	}

	// Fork the process
	pid = fork();
	
	if (pid == -1)
	{
		perror("fork");
		free(read_msg);
		return 1;
	}

	if (pid == 0)
	{ // Child process
		close(pipefd[1]); // Close the write end

		// Read from the pipe in chunks
		while ((bytes_read = read(pipefd[0], read_msg + total_size,
					current_size - total_size - 1)) > 0)
		{
			total_size += bytes_read;
			
			// If buffer is full, double its size
			if (total_size >= current_size - 1)
			{
				current_size *= 2;
				read_msg = realloc(read_msg, current_size);
				if (read_msg == NULL)
				{
					perror("realloc");
					close(pipefd[0]);
					return 1;
				}
			}
		}

		read_msg[total_size] = '\0'; // Null-terminate the string
		printf("Child Process: Read \"%s\" from pipe\n", read_msg);
		close(pipefd[0]); // Close the read end
	}
	else
	{ // Parent process
		close(pipefd[0]); // Close the read end
		write(pipefd[1], write_msg, strlen(write_msg)); // Write to the pipe
		close(pipefd[1]); // Close the write end
		wait(NULL); // Wait for the child process to finish
	}

	free(read_msg); // Free allocated memory
	return 0;
}
