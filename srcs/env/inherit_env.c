#include "env.h"

t_env	*push_env(t_env *env, char *val)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	env->next = new_env;
	new_env->val = ft_strdup(val);
	new_env->next = NULL;
	return (new_env);
}

t_env	*inherit_env(void)
{
	t_env	*env;
	t_env	head;
	int		i;

	head.next = NULL;
	env = &head;
	i = 0;
	while (environ[i])
	{
		env = push_env(env, environ[i]);
		i++;
	}
	return (head.next);
}
