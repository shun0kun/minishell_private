#include "env.h"

int	is_same_name(char *s1, char *s2)
{

}

void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s\n", env->val);
		env = env->next;
	}
}

int	env_add(t_env *env, const char *name, const char *val)
{
	t_env	*new_env;

	while (1)
	{
		if (is_same_name(env->val, name))
		{
			env->val = ft_strcat(env->val, val);
			if (!env->val)
				return (-1);
			return (0);
		}
		if (!env->next)
			break ;
		env = env->next;
	}
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (-1);
	env->next = new_env;
	new_env->val = ft_strcat(name, val);
	if (!new_env->val)
		return (-1);
	new_env->next = NULL;
	return (0);
}

void	env_del(t_env *env, const char *name)
{
	t_env	*prev;

	while (env)
	{
		if (is_same_name(env->val, name))
		{
			prev->next = env->next;
			free(env->val);
			free(env);
		}
		prev = env;
		env = env->next;
	}
}
