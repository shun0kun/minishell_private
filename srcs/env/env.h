#ifndef ENV_H
# define ENV_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../ft/ft.h"

extern char	**environ;

typedef struct s_env
{
	char			*name;
	char			*val;
	int				is_exported;
	struct s_env	*next;
}	t_env;

t_env	*push_env(t_env *env, char *val);
t_env	*inherit_env(void);
void	print_env(t_env *env);

#endif