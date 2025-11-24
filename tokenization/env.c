#include "../minishell.h"
#include "private.h"

int	get_env(char **env_val, char *str)
{
	int		i;
	char	*env;
	
	if (*str != '$')
		return (-1);
	str++;
	i = 0;
	while (str[i] && (str[i] == '_' || is_number(str[i]) || is_alphabet(str[i])))
	{
		i++;
	}
	env = ft_strndup(str, i);
	*env_val = getenv(env);
	free(env);
	return (i + 1);
}