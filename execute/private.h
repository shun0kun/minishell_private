#ifndef PRIVATE_H
# define PRIVATE_H

# include "../minishell.h"

int	execute_pipeline(t_node *node, int *exit_status, t_env *env);

#endif