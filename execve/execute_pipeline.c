#include "private.h"

void	invalidate_pipefd(int pipefd[2])
{
	pipefd[0] = -1;
	pipefd[1] = -1;
}

void	close_pipefd(int pipefd[2])
{
	if (pipefd[0] >= 0)
		close(pipefd[0]);
	if (pipefd[1] >= 0)
		close(pipefd[1]);
	pipefd[0] = -1;
	pipefd[1] = -1;
}

void	wait_all_pid(pid_t last_pid, int *exit_status)
{
	pid_t	pid;
	int		status;

	if (last_pid < 0)
	{
		while (waitpid(-1, NULL, 0) > 0)
			;
		*exit_status = 1;
		return ;
	}
	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				*exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				*exit_status = 128 + WTERMSIG(status);
		}
		else if (pid < 0)
			break ;
	}
}

void	execute_pipeline(t_node *node, int *exit_status)
{
	t_pipeline	*pl;
	pid_t		pid;
	int			pipefd_prev[2];
	int			pipefd_cur[2];

	pl = node->pipeline;
	invalidate_pipefd(pipefd_cur);
	invalidate_pipefd(pipefd_cur);
	while (pl)
	{
		if (pl->next)
		{
			if (pipe(pipefd_cur) < 0)
			{
				close_pipefd(pipefd_prev);
				wait_all_pid(-1, exit_status);
				return (-1);
			}
		}
		pid = fork();
		if (pid == 0)
			child(pipefd_prev, pipefd_cur, pl);
		else if (pid < 0)
		{
			close_pipefd(pipefd_prev);
			close_pipefd(pipefd_cur);
			wait_all_pid(-1, exit_status);
			return (-1);
		}
		close_pipefd(pipefd_prev);
		pipefd_prev[0] = pipefd_cur[0];
		pipefd_prev[1] = pipefd_cur[1];
		invalidate_pipefd(pipefd_cur);
		pl = pl->next;
	}
	wait_all_pid(pid, exit_status);
	return (0);
}
