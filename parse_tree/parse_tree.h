#ifndef PARSE_TREE_H
# define PARSE_TREE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../common_def.h"

typedef enum e_ast_node_type
{
	CMD,
	PIPE,
	ANDOR
}	t_ast_node_type;

typedef enum e_redirect_type
{
	R,
	RR,
	L,
	LL
}	t_redirect_type;

typedef enum e_andor
{
	AND,
	OR
}	t_andor;

typedef struct s_redirect
{
	t_redirect_type		type;
	char				*filename;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd_data
{
	char		**argv;
	t_redirect	*red;
}	t_cmd_data;

typedef union u_ast_node_data
{
	t_cmd_data	cmd;
	t_andor		ao;
}	t_ast_node_data;

typedef struct s_ast_node
{
	t_ast_node_type		type;
	t_ast_node_data		data;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
} t_ast_node;

#endif
