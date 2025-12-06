// #define rep(i,n) for (int i = 0; i < (n); ++i)

// void print_ast(t_node *node)
// {
//     static const char	*nds[] = {"ND_PIPELINE","ND_AND","ND_OR"};
//     static const int width = 3;
//     static int depth = 1;
//     static int is_right = 1;
//     static long long mask=0;

//     mask = (mask & ~(1<<depth)) | ((!is_right) << depth);
//     if(depth >= 3)for(int i=2;i<depth;i++){
//         printf("%s",(mask & 1<<i)?"│":" ");
//         rep(i,width)printf(" ");
//     }
//     if(depth>=2){
//         printf("%s",is_right?"└":"├");
//         rep(i,width)printf("─");
//         printf(" ");
//     }
// 	printf("%s\n",nds[node->kind]);
// 	if(node->kind == ND_PIPELINE)
// 		return;
// 	is_right = 0;
// 	depth++;
// 	print_ast(node->lhs);
// 	is_right = 1;
// 	print_ast(node->rhs);
// 	depth--;
// }


// void	print_tokens(t_token *token)
// {
// 	char *arr[] = {"TK_WORD", "TK_REDIR", "TK_PIPE", "TK_LPAREN", "TK_RPAREN", "TK_AND", "TK_OR", "TK_EOF", NULL};

// 	if (!token)
// 	{
// 		printf("つくれてない\n");
// 		return ;
// 	}
// 	while (token->kind != TK_EOF)
// 	{
// 		printf("%-20s[%s]\n", arr[token->kind], token->value);
// 		token = token->next;
// 	}
// 	printf("%s\n", arr[token->kind]);
// }