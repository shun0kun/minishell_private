#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../ft/ft.h"

# include <string.h>

void	setup_child1_io(int *fd_pipe, char *infile);
void	setup_child2_io(int *fd_pipe, char *infile);
void	exec_cmd(char *arg, char **envp);
void	child1(int *fd_pipe, char **argv, char **envp);
void	child2(int *fd_pipe, char **argv, char **envp);

char	*get_env(char **envp, char *name);
char	*create_next_path(char **p_path_set, char *cmd_name);
char	*find_path(char *path_set, char *cmd_name);
char	*get_path(char **envp, char *cmd_name);

char	**get_cmd(char *s);

void	error_exit(void);
void	free_strs(char **strs);
size_t	ft_strlen_until(const char *s, char c);

#endif