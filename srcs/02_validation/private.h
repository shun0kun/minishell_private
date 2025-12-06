#ifndef PRIVATE_H
# define PRIVATE_H

# include "../minishell.h"

typedef enum e_state
{
	START,
	AFTER_WORD,
	AFTER_RED,
	AFTER_PIPE,
	AFTER_ANDOR,
	AFTER_PARENS,
	ERROR
}	t_state;

#endif