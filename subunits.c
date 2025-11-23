#include "header.h"

int	is_number(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_alphabet(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_operator(char *str)
{
	int	flag;

	flag = 0;
	if (*str == '>' || *str == '<')
		flag = 1;
	else if (*str == '|')
		flag = 1;
	else if (*str == '&' && *(str + 1) == '&')
		flag = 1;
	else if (*str == '(' || *str == ')')
		flag = 1;
	return (flag);
}

t_token	*new_token(t_token *token)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	new_token->type = TOK_NO;
	new_token->value = NULL;
	new_token->next = NULL;
	token->next = new_token;
	return (new_token);
}

t_token	*get_last_token(t_token *token)
{
	while (token->next)
	{
		token = token->next;	
	}
	return (token);
}

t_token_type	get_operation_token_type(char *str)
{
	if (*str == '(')
		return (TOK_KAKKOO);
	else if (*str == ')')
		return (TOK_KAKKOC);
	else if (*str == '&' && *(str + 1) == '&')
		return (TOK_ANDOR);
	else if (*str == '|' && *(str + 1) == '|')
		return (TOK_ANDOR);
	else if (*str == '|')
		return (TOK_PIPE);
	else if (*str == '<' || *str == '>')
		return (TOK_RED);
	else
		return (TOK_NO);
}

int	get_operation_value(t_token *token, char *str)
{
	if (!token || !str)
		return (-1);
	if (token->type == TOK_PIPE || token->type == TOK_KAKKOO || token->type == TOK_KAKKOC || (token->type == TOK_RED && *str != *(str + 1)))
	{
		token->value = malloc(sizeof(char) * 2);
		if (!token->value)
			return (-1);
		token->value[0] = *str;
		token->value[1] = '\0';
		return (1);
	}
	else if (token->type == TOK_ANDOR || (token->type == TOK_RED && *str == *(str + 1)))
	{
		token->value = malloc(sizeof(char) * 3);
		if (!token->value)
			return (-1);
		token->value[0] = str[0];
		token->value[1] = str[1];
		token->value[2] = '\0';
		return (2);
	}
	else
		return (-1);
}

int	get_word_value(t_token *token, char *str)
{
	int		i;
	t_state	state;
	t_buf	buf;
	char	*env_val;

	buf_init(&buf);
	i = 0;
	state = OUT_QUOTE;
	while (str[i])
	{
		if (state == OUT_QUOTE)
		{
			if (is_space(str[i]) || is_operator(str + i))
				break ;
			else if (str[i] == '\'')
				state = IN_SINGLE;
			else if (str[i] == '"')
				state = IN_DOUBLE;
			else if (str[i] == '$' && (str[i + 1] == '_' || is_alphabet(str[i + 1])))
			{
				i += get_env(&env_val, str + i);
				if (!env_val)
					continue ;
				while (*env_val)
				{
					if (is_space(*env_val))
					{
						while (is_space(*env_val))
							env_val++;
						buf_add(&buf, '\0');
						token->value = buf.data;
						buf_init(&buf);
						token = new_token(token);
						token->type = TOK_WORD;
						continue ;
					}
					else
					{
						buf_add(&buf, *env_val);
					}
					env_val++;
				}
				continue ;
			}
			else
				buf_add(&buf, str[i]);
		}
		else if (state == IN_SINGLE)
		{
			if (str[i] == '\'')
				state = OUT_QUOTE;
			else
				buf_add(&buf, str[i]);
		}
		else
		{
			if (str[i] == '"')
				state = OUT_QUOTE;
			else if (str[i] == '$' && (str[i + 1] == '_' || is_alphabet(str[i + 1])))
			{
				i += get_env(&env_val, str + i);
				if (!env_val)
					continue ;
				while (*env_val)
				{
					buf_add(&buf, *env_val);
					env_val++;
				}
				continue ;
			}
			else
				buf_add(&buf, str[i]);
		}
		i++;
	}
	buf_add(&buf, '\0');
	token->value = buf.data;
	return (i);
}

// token->value = ft_strndup(str, i);
// if (!token->value)
// 	return (-1);
