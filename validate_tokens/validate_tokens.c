#include "validate_tokens.h"

t_state_val	transition_start(t_token_type a, unsigned int *paren_depth)
{
	if (a == TOK_WORD)
		return(AFTER_WORD);
	else if (a == TOK_RED)
		return (AFTER_RED);
	else if (a == TOK_PIPE || a == TOK_ANDOR || a == TOK_KAKKOC)
		return(ERROR);
	else if (a == TOK_KAKKOO)
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

t_state_val	transition_afterword(t_token_type a, unsigned int *paren_depth)
{
	if (a == TOK_WORD)
		return (AFTER_WORD);
	else if (a == TOK_RED)
		return (AFTER_RED);
	else if (a == TOK_PIPE)
		return (AFTER_PIPE);
	else if (a == TOK_ANDOR)
		return (AFTER_ANDOR);
	else if (a == TOK_KAKKOO || (a == TOK_KAKKOC && *paren_depth == 0))
		return (ERROR);
	else if (a == TOK_KAKKOC && *paren_depth > 0)
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

t_state_val	transition_afterred(t_token_type a, unsigned int *paren_depth)
{
	(void)paren_depth;
	if (a == TOK_WORD)
		return (AFTER_WORD);
	else
		return (ERROR);
}

t_state_val	transition_afterpipe(t_token_type a, unsigned int *paren_depth)
{
	(void)paren_depth;
	if (a == TOK_WORD)
		return (AFTER_WORD);
	else
		return (ERROR);
}

t_state_val	transition_afterandor(t_token_type a, unsigned int *paren_depth)
{
	if (a == TOK_WORD)
		return (AFTER_WORD);
	else if (a == TOK_KAKKOO)
	{
		*paren_depth += 1;
		return (START);
	}
	else
		return (ERROR);
}

t_state_val	transition_afterparens(t_token_type a, unsigned int *paren_depth)
{
	if (a == TOK_ANDOR)
		return (AFTER_ANDOR);
	else if (a == TOK_KAKKOC && *paren_depth > 0)
	{
		*paren_depth -= 1;
		return (AFTER_PARENS);
	}
	else if (a == TOK_EOF && *paren_depth == 0)
	{
		return (AFTER_PARENS);
	}
	else
		return (ERROR);
}

t_state_val	transition_error(t_token_type a, unsigned int *paren_depth)
{
	(void)a;
	(void)paren_depth;
	return (ERROR);
}

t_state_val	transition_ver1(t_state_val state, t_token_type a, unsigned int *paren_depth)
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

t_state_val	transition_ver2(t_state_val state, t_token_type a, unsigned int *paren_depth)
{
	static t_state_val	(*transition_fns[])(t_token_type, unsigned int *) = {transition_start, transition_afterword, transition_afterred, transition_afterpipe, transition_afterandor, transition_afterparens, transition_error};

	return (transition_fns[state](a, paren_depth));
}

int	validate_tokens(t_token *token)
{
	t_state_val		state;
	unsigned int	paren_depth;

	state = START;
	paren_depth = 0;
	while (token)
	{
		state = transition_ver2(state, token->type, &paren_depth);
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