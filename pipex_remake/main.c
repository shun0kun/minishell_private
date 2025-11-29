#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	fd_pipe[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		return (-1);
	if (pipe(fd_pipe) < 0)
		return (-1);
	pid1 = fork();
	if (pid1 < 0)
		return (-1);
	else if (pid1 == 0)
		child1(fd_pipe, argv, envp);
	pid2 = fork();
	if (pid2 < 0)
		return (-1);
	else if (pid2 == 0)
		child2(fd_pipe, argv, envp);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
