#include "private.h"

int	ft_strlen_until(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] || s[len] != c)
		len++;
	return (len);
}

char	*get_env(t_env *env, char *name)
{
	t_env	*node;

	node = env;
	while (node)
	{
		if (ft_strcmp(node->name, name) == 0 && node->val)
			return (node->val);
		node = node->next;
	}
	return (NULL);
}

char	*create_next_path(char **p_path_set, char *cmd_name)
{
	char	*path_set = *p_path_set;
	char	*path;
	int		i;
	int		j;

	path = malloc(ft_strlen_until(path_set, ':') + ft_strlen(cmd_name) + 2);
	if (!path)
		return (NULL);
	i = 0;
	while (*path_set)
	{
		path[i] = path_set[i];
		i++;
	}
	*p_path_set += i;
	if (path_set[i + 1] == ':')
		(*p_path_set)++;
	path[i++] = '/';
	j = 0;
	while (cmd_name[j])
	{
		path[i + j] = cmd_name[j];
		j++;
	}
	path[i + j] = '\0';
	return (path);
}

char	*find_cmd_path(char *path_set, char *cmd_name)
{
	char	*path;

	while (*path_set)
	{
		path = create_next_path(&path_set, cmd_name);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

char	*get_path(t_env *env, char *cmd_name)
{
	char	*path;
	char	*path_set;

	path_set = get_env(env, "PATH");
	if (!path_set)
		return (NULL);
	path = find_cmd_path(path_set, cmd_name);
	if (!path)
		return (NULL);
	return (path);
}

void	setup_child_io(int pipefd_prev[2], int pipefd_cur[2], t_redir *redir)
{
	int	fd;

	if (pipefd_prev[0] >= 0)
		dup2(pipefd_prev[0], STDIN_FILENO);
	if (pipefd_cur[1] >= 0)
		dup2(pipefd_cur[1], STDOUT_FILENO);
	close_pipefd(pipefd_prev);
	close_pipefd(pipefd_cur);
	while (redir)
	{
		if (redir->kind == IN)
		{
			fd = open(redir->filename, O_RDONLY);
			if (fd < 0)
				exit(1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->kind == HEREDOC)
		{
			dup2(redir->heredoc_fd, STDIN_FILENO);
			close(redir->heredoc_fd);
		}
		else if (redir->kind == OUT)
		{
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				exit(1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->kind == APPEND)
		{
			fd = open(redir->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (fd < 0)
				exit(1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
}

void	exec_cmd(char **argv, t_env *env)
{
	char	*path;
	char	**envp;
	int		saved_error;

	path = get_path(env, argv[0]);
	if (!path)
	{
		if (errno == ENOMEM)
			exit(1);
		else
			exit(127);
	}
	envp = make_envp(env);
	execve(path, argv, envp);
	saved_error = errno;
	free(path);
	free(envp);
	if (saved_error == ENOENT || saved_error == ENOTDIR)
		exit(127);
	else if (saved_error == EACCES || saved_error == EISDIR || saved_error == ENOEXEC || saved_error == ETXTBSY)
		exit(126);
	else
		exit(1);
}

void	child(int pipefd_prev[2], int pipefd_cur[2], t_pipeline *pipeline, t_env *env)
{
	setup_child_io(pipefd_prev, pipefd_cur, pipeline->redir);
	exec_cmd(pipeline->argv, env);
}
