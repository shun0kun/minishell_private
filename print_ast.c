#include "minishell.h"

#define rep(i,n) for (int i = 0; i < (n); ++i)

void print_cmd_node(t_node *node)
{
    const char *red_types[] = {"IN","OUT","APPEND","HEREDOC"};
    int i = 0;
    t_redir *cur = node->cmd->redir;

    printf("ND_CMD: {");
    printf("args: ");
    printf("[");
    while(node->cmd->argv[i]){
        printf("`%s'%s",node->cmd->argv[i],node->cmd->argv[i+1]?", ":"");
        i++;
    }
    printf("], ");
    printf("reds: ");
    printf("[");
    while(cur)
    {
        printf("(%s)`%s'%s" ,red_types[cur->kind],cur->filename,cur->next?", ":"");
        cur = cur->next;
    }
    printf("]");
    printf("}\n");
}

void print_ast(t_node *node)
{
    static const char *nds[]={"ND_CMD","ND_PIPE","ND_AND","ND_OR"};
    static const int width = 3;
    static int depth = 1;
    static int is_right = 1;
    static long long mask=0;

    mask = (mask & ~(1<<depth)) | ((!is_right) << depth);
    if(depth >= 3)for(int i=2;i<depth;i++){
        printf("%s",(mask & 1<<i)?"│":" ");
        rep(i,width)printf(" ");
    }
    if(depth>=2){
        printf("%s",is_right?"└":"├");
        rep(i,width)printf("─");
        printf(" ");
    }
    if(node->kind == ND_CMD)print_cmd_node(node);
    else 
    {
        printf("%s\n",nds[node->kind]);
        is_right = 0;
        depth++;
        print_ast(node->lhs);
        is_right = 1;
        print_ast(node->rhs);
        depth--;
    }
}
