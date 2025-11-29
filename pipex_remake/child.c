#include "pipex.h"

void	setup_child1_io(int *fd_pipe, char *infile)
{
	int	fd_in;

	fd_in = open(infile, O_RDONLY);
	if (fd_in < 0)
		error_exit();
	if (dup2(fd_in, STDIN_FILENO) < 0)
	{
		close(fd_in);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		error_exit();
	}
	close(fd_in);
	if (dup2(fd_pipe[1], STDOUT_FILENO) < 0)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		error_exit();
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
}

void	setup_child2_io(int *fd_pipe, char *infile)
{
	int	fd_out;

	fd_out = open(infile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
		error_exit();
	if (dup2(fd_out, STDOUT_FILENO) < 0)
	{
		close(fd_out);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		error_exit();
	}
	close(fd_out);
	if (dup2(fd_pipe[0], STDIN_FILENO) < 0)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		error_exit();
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
}

void	exec_cmd(char *arg, char **envp)
{
	char	*path;
	char	**cmd;

	cmd = get_cmd(arg);
	if (!cmd)
		error_exit();
	path = get_path(envp, cmd[0]);
	if (!path)
	{
		free_strs(cmd);
		error_exit();
	}
	if (execve(path, cmd, envp) < 0)
	{
		free_strs(cmd);
		free(path);
		error_exit();
	}
}

void	child1(int *fd_pipe, char **argv, char **envp)
{
	setup_child1_io(fd_pipe, argv[1]);
	exec_cmd(argv[2], envp);
}

void	child2(int *fd_pipe, char **argv, char **envp)
{
	setup_child2_io(fd_pipe, argv[4]);
	exec_cmd(argv[3], envp);
}
