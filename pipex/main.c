#include "pipex.h"

void	free_cmd(char **cmd)
{
	if (!cmd)
		return ;
	for (int i = 0; cmd[i]; i++)
		free(cmd[i]);
	free(cmd);
}

int	ft_pathlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != ':')
		len++;
	return (len);
}

char	*get_path(char **envp, char *cmd)
{
	char				*paths = NULL;
	const char			*name = "PATH=";
	int					flag;
	int					cmd_len = ft_strlen(cmd);
	int					path_len;
	char				*path;
	int					i, j;

	for (int i = 0; envp[i]; i++)
	{
		flag = 1;
		for (int j = 0; j < 5; j++)
		{
			if (envp[i][j] != name[j])
				flag = 0;
		}
		if (flag == 1)
		{
			paths = envp[i] + 5;
			break ;
		}
	}
	if (!paths)
		return (NULL);
	while (*paths)
	{
		path_len = ft_pathlen(paths);
		path = malloc(path_len + 1 + cmd_len + 1);
		if (!path)
			return (NULL);
		i = 0;
		while (paths[i] && paths[i] != ':')
		{
			path[i] = paths[i];
			i++;
		}
		paths += i;
		path[i++] = '/';
		j = 0;
		while (cmd[j])
		{
			path[i + j] = cmd[j];
			j++;
		}
		path[i + j] = '\0';
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
			{
				return (path);
			}
			printf("permission denied: %s\n", cmd);
			free(path);
			return (NULL);
		}
		if (*paths == ':')
			paths++;
		free(path);
	}
	printf("command not found: %s\n", cmd);
	return (NULL);
}

char	**get_cmd(char *cmd)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * 2);
	if (!res)
		return (NULL);
	res[0] = malloc(ft_strlen(cmd) + 1);
	if (!res[0])
	{
		free(res);
		return (NULL);
	}
	i = 0;
	while (cmd[i])
	{
		res[0][i] = cmd[i];
		i++;
	}
	res[0][i] = '\0';
	res[1] = NULL;
	return (res);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd_pipe[2];
	int		fd_redirect;
	pid_t	pid1;
	pid_t	pid2;
	char	*path;
	char	**cmd;

	if (argc != 5)
		return (-1);
	if (pipe(fd_pipe) < 0)
		return (-1);
	pid1 = fork();
	if (pid1 < 0)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		return (-1);
	}
	if (pid1 == 0)
	{
		fd_redirect = open(argv[1], O_RDONLY);
		if (fd_redirect < 0)
			return (-1);
		dup2(fd_redirect, STDIN_FILENO);
		close(fd_redirect);
		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		path = get_path(envp, argv[2]);
		if (!path)
			return (-1);
		cmd = get_cmd(argv[2]);
		if (!cmd)
		{
			free(path);
			return (-1);
		}
		if (execve(path, cmd, envp) < 0)
		{
			free(path);
			free_cmd(cmd);
			return (-1);
		}
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		return (-1);
	}
	if (pid2 == 0)
	{
		fd_redirect = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_redirect < 0)
			return (-1);
		dup2(fd_redirect, STDOUT_FILENO);
		close(fd_redirect);
		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		path = get_path(envp, argv[3]);
		if (!path)
			return (-1);
		cmd = get_cmd(argv[3]);
		if (!cmd)
		{
			free(path);
			return (-1);
		}		
		if (execve(path, cmd, envp) < 0)
		{
			free_cmd(cmd);
			free(path);
			return (-1);
		}
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
