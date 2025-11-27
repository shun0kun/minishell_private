#include "private.h"

void	execute_pipeline(t_node *node, int *exit_status)
{
	int		fd[2];
	pid_t	pid;

	while (1)
	{
		pid = pipe(fd);
		if (pid < 0)
		{
			*exit_status = 1;
			return ;
		}
		dup2(stdout, fd[0]);
		if (pid > 0)
		{
			close(fd[1]);
		}
		else if (pid == 0)
		{
			close(fd[0]);
			f();
		}
		else
		{
			*exit_status = 1;
			return ;
		}
	}
}
