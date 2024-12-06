/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:47:05 by ihajouji          #+#    #+#             */
/*   Updated: 2024/08/26 06:52:56 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"
#include <limits.h>

void	add_oldpwd(t_env **env)
{
	t_env	*temp;
	char	cwd[PATH_MAX];
	char	*tmp;

	temp = *env;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		while (temp)
		{
			if (ft_strncmp(temp->var, "OLDPWD", 6) == 0)
			{
				free(temp->var);
				temp->var = ft_strjoin("OLDPWD=", cwd);
				return ;
			}
			temp = temp->next;
		}
		if (!temp)
		{
			tmp = ft_strjoin("OLDPWD=", cwd);
			ft_lstadd_back(env, ft_lstnew(tmp));
			free(tmp);
		}
	}
	return ;
}

void	change_pwd(t_env **env)
{
	t_env	*temp;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		temp = *env;
		while (temp)
		{
			if (ft_strncmp(temp->var, "PWD", 3) == 0)
			{
				free(temp->var);
				temp->var = ft_strjoin("PWD=", cwd);
				break ;
			}
			temp = temp->next;
		}
	}
}

int	ft_cd(char **words, t_env **env)
{
	char	*path;
	t_env	*temp;

	temp = *env;
	add_oldpwd(env);
	if (!words[1] || ft_strncmp(words[1], "~", 1) == 0)
	{
		while (temp)
		{
			if (ft_strncmp(temp->var, "HOME", 4) == 0)
			{
				path = temp->var + 5;
				break ;
			}
			temp = temp->next;
		}
		if (!temp)
			return (printf("no home variable is set\n"), g_es = 1, 1);
	}
	else
		path = words[1];
	if (chdir(path) != 0)
		return (printf("cd: %s: NO such file or directory\n", path),
			g_es = 1, 1);
	return (change_pwd(env), g_es = 0, 0);
}
