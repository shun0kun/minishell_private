/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimots <sshimots@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:21:34 by sonakamu          #+#    #+#             */
/*   Updated: 2025/12/04 14:43:46 by sshimots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_pwd_oldpwd(char **envp)
{
	char	*pwd;
	char	*new_pwd;

	pwd = get_env(envp, "PWD");
	if (pwd)
		add_env(envp, "OLDPWD", pwd);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		//error message
		return ;
	}
	add_env(envp, "PWD", new_pwd);
	free(new_pwd);
}

int builtin_cd(char **argv)
{
	int		argc;
	char	*path;
	char	**envp;//

	argc = 0;
	while (argv[argc])
		argc++;
	if(argc == 1)
	{
		path = get_env(envp, "HOME");
		if (!path)
			return (1);
	}
	else if (argc == 2)
	{
		path = argv[1];
	}
	else
	{
		//error message
		return (1);
	}
	if (chdir(path) < 0)
	{
		//error message
		return (1);
	}
	update_pwd_oldpwd(envp);
	return (0);
}

typedef struct s_shell
{
	char	*envp;
	char	*pwd;
	int		*exit_status;
}	t_shell;
