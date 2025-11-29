#include "pipex.h"

char	*get_env(char **envp, char *name)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], name, ft_strlen(name)) == 0 && envp[i][ft_strlen(name)] == '=')
			return (envp[i] + ft_strlen(name) + 1);
		i++;
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
	while (cmd_name[j])
	{
		path[i + j] = cmd_name[j];
		j++;
	}
	path[i + j] = '\0';
	return (path);
}

char	*find_path(char *path_set, char *cmd_name)
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

char	*get_path(char **envp, char *cmd_name)
{
	char				*path_set;
	char				*path;

	path_set = get_env(envp, "PATH");
	if (!path_set)
		error_exit();
	path = find_path(path_set, cmd_name);
	if (!path)
		error_exit();
	return (path);
}
