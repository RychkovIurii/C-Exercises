/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:13:41 by irychkov          #+#    #+#             */
/*   Updated: 2024/08/13 13:40:04 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
//#include <process.h> // for Windows
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int	main(int argc, char *argv[])
{

	/* execl(
			"C:\\Windows\\System32\\ping.exe",
			"C:\\Windows\\System32\\ping.exe",
			"google.com",
			NULL
		); */ // for Windows


	/* execlp(
			"ping",
			"ping",
			"google.com",
			NULL
		); */ // for Windows and looking for a PATH


	/* execl("ping", "ping", "google.com", NULL); // EXECL Does not search the directories listed in the PATH environment variable. Use EXECLP */


	/* execl("/bin/ping", "/bin/ping", "google.com", NULL); //It works */


	/*
	//execv: Similar to execl, but arguments are passed as an array.
	char *args[] = {"ping", "google.com", "-c", "3", NULL};
	execv("/bin/ping", args);
	printf("Success! (execv)"); // This line will not be executed if execv is successful
	*/


	/*
	//execvp: Similar to execv, but searches for the executable in PATH.
	char *args[] = {"ping", "google.com", "-c", "3", NULL};
	execvp("ping", args);
	printf("Success! (execvp)"); // This line will not be executed if execvp is successful
	*/


	/*
	//int execvpe(const char *file, char *const argv[], char *const envp[]); 
	char *args[] = {"ping", "google.com", "-c", "3", NULL};
	char *envp[] = {"PATH=/usr/bin:/bin", NULL}; // Example custom environment

	// execvpe: Searches for "ping" in the specified PATH and uses custom environment
	if (execvpe("ping", args, envp) == -1) {
		perror("execvpe failed");
		return 1;
	}
	printf("Success!"); // This line will not be executed if execvpe is successful
	*/


	/* 
	//int execve(const char *pathname, char *const argv[], char *const envp[]);
	char *args[] = {"ping", "google.com", "-c", "3", NULL};
	char *envp[] = {"PATH=/usr/bin:/bin", NULL};

	if (execve("/bin/ping", args, envp) == -1) {
		// Print an error message if execve fails
		perror("execve failed");
		return 1;
	}
	 */


	execlp("ping", "ping", "-c", "3", "google.com", NULL);
	//execlp("pingr", "ping", "-c", "3", "google.com", NULL); // With error

	int	err = errno;

	printf("Ping finished executing with %d\n", err); //This line will not be executed if execlp is successful
	return (0);
}
