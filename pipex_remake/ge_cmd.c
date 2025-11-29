#include "pipex.h"

char	**get_cmd(char *s)
{
	char	**cmd;

	cmd = ft_split(s, ' ');
	if (!cmd)
	{
		free_strs(cmd);
		return (NULL);
	}
	return (cmd);
}
