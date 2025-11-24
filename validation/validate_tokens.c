#include "../minishell.h"
#include "private.h"

t_state	transition_start(t_token_kind a, unsigned int *paren_depth)
{
	if (a == TK_WORD)
		return(AFTER_WORD);
	else if (a == TK_REDIR)
		return (AFTER_RED);
	else if (a == TK_PIPE || a == TK_AND || a == TK_OR || a == TK_RPAREN)
		return(ERROR);
	else if (a == TK_LPAREN)
	{
		*paren_depth += 1;
		return(START);
	}
	else
	{
		if (*paren_depth > 0)
			return(ERROR);
		return (START);
	}
}

t_state	transition_afterword(t_token_kind a, unsigned int *paren_depth)
{
	if (a == TK_WORD)
		return (AFTER_WORD);
	else if (a == TK_REDIR)
		return (AFTER_RED);
	else if (a == TK_PIPE)
		return (AFTER_PIPE);
	else if (a == TK_AND || a == TK_OR)
		return (AFTER_ANDOR);
	else if (a == TK_LPAREN || (a == TK_RPAREN && *paren_depth == 0))
		return (ERROR);
	else if (a == TK_RPAREN && *paren_depth > 0)
	{
		*paren_depth -= 1;
		return (AFTER_PARENS);
	}
	else
	{
		if (*paren_depth > 0)
			return (ERROR);
		return (AFTER_WORD);
	}
}

t_state	transition_afterred(t_token_kind a, unsigned int *paren_depth)
{
	(void)paren_depth;
	if (a == TK_WORD)
		return (AFTER_WORD);
	else
		return (ERROR);
}

t_state	transition_afterpipe(t_token_kind a, unsigned int *paren_depth)
{
	(void)paren_depth;
	if (a == TK_WORD)
		return (AFTER_WORD);
	else
		return (ERROR);
}

t_state	transition_afterandor(t_token_kind a, unsigned int *paren_depth)
{
	if (a == TK_WORD)
		return (AFTER_WORD);
	else if (a == TK_LPAREN)
	{
		*paren_depth += 1;
		return (START);
	}
	else
		return (ERROR);
}

t_state	transition_afterparens(t_token_kind a, unsigned int *paren_depth)
{
	if (a == TK_AND || a == TK_OR)
		return (AFTER_ANDOR);
	else if (a == TK_RPAREN && *paren_depth > 0)
	{
		*paren_depth -= 1;
		return (AFTER_PARENS);
	}
	else if (a == TK_EOF && *paren_depth == 0)
	{
		return (AFTER_PARENS);
	}
	else
		return (ERROR);
}

t_state	transition_error(t_token_kind a, unsigned int *paren_depth)
{
	(void)a;
	(void)paren_depth;
	return (ERROR);
}

t_state	transition_ver1(t_state state, t_token_kind a, unsigned int *paren_depth)
{
	if (state == START)
		return (transition_start(a, paren_depth));
	else if (state == AFTER_WORD)
		return (transition_afterword(a, paren_depth));
	else if (state == AFTER_RED)
		return (transition_afterred(a, paren_depth));
	else if (state == AFTER_PIPE)
		return (transition_afterpipe(a, paren_depth));
	else if (state == AFTER_ANDOR)
		return (transition_afterandor(a, paren_depth));
	else if (state == AFTER_PARENS)
		return (transition_afterparens(a, paren_depth));
	else
		return (transition_error(a, paren_depth));
}

t_state	transition_ver2(t_state state, t_token_kind a, unsigned int *paren_depth)
{
	static t_state	(*transition_fns[])(t_token_kind, unsigned int *) = {transition_start, transition_afterword, transition_afterred, transition_afterpipe, transition_afterandor, transition_afterparens, transition_error};

	return (transition_fns[state](a, paren_depth));
}

int	validate_tokens(t_token *token)
{
	t_state		state;
	unsigned int	paren_depth;

	state = START;
	paren_depth = 0;
	while (token)
	{
		state = transition_ver2(state, token->kind, &paren_depth);
		token = token->next;
	}
	if (state == ERROR)
		return (0);
	return (1);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// char *arr[] = {"START", "AFTER_WORD", "AFTER_RED", "AFTER_PIPE", "AFTER_ANDOR", "AFTER_PARENS", "ERROR"};
// printf("{%s}->", arr[state]);
// printf("{%s}->", arr[state]);
// fflush(stdout);
// printf("end");