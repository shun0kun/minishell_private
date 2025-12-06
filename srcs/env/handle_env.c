#include "env.h"

int	is_same_env_name(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if ((!s1[i] || s1[i] == '=') && (!s2[i] || s2[i] == '='))
		return (1);
	return (0);
}

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->val)
			printf("%s=%s\n", env->name, env->val);
		env = env->next;
	}
}

int	env_add(t_env *env, const char *name, const char *val)
{
	t_env	*new_env;

	while (1)
	{
		if (is_same_env_name(env->val, name))
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
		if (is_same_env_name(env->val, name))
		{
			prev->next = env->next;
			free(env->val);
			free(env);
		}
		prev = env;
		env = env->next;
	}
}
