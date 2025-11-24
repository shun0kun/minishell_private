#include "../minishell.h"
#include "private.h"

t_token *tokenize(char *str)
{
	int		i;
	t_token	*token;
	t_token head;

	token = &head;
	// head.kind = TK_NO;
	head.value = NULL;
	head.next = NULL;
	i = 0;
	while (str[i])
	{
		if (is_space(str[i]))
		{
			while (is_space(str[i]))
				i++;
		}
		else if (is_operator(str + i))
		{
			token = new_token(token);
			token->kind = get_operation_token_type(str + i);
			i += get_operation_value(token, str + i);
		}
		else
		{
			token = new_token(token);
			token->kind = TK_WORD;
			i += get_word_value(token, str + i);
			token = get_last_token(token);
		}
	}
	token = new_token(token);
	token->kind = TK_EOF;
	token->value = NULL;
	token->next = NULL;
	return (head.next);
}

// $? →　終了コードの環境変数。今度実装する。
// * →　ワイルドカード。今度実装する。
