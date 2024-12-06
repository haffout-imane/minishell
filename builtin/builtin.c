/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:19:40 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/07 12:50:17 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	check_builtin(char *str)
{
	if (!str)
		return (0);
	else if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	else
		return (0);
}

int	is_builtin(char **words, t_env **my_env, t_minishell *line)
{
	if (!words || !*words)
		return (0);
	if (ft_strcmp(words[0], "echo") == 0)
		return (ft_echo(words), 1);
	else if (ft_strcmp(words[0], "pwd") == 0)
		return (ft_pwd(my_env), 1);
	else if (ft_strcmp(words[0], "env") == 0)
		return (ft_env(my_env), 1);
	else if (ft_strcmp(words[0], "cd") == 0)
		return (ft_cd(words, my_env), 1);
	else if (ft_strcmp(words[0], "export") == 0)
		return (ft_export(words, my_env), 1);
	else if (ft_strcmp(words[0], "unset") == 0)
		return (ft_unset(words, my_env), 1);
	else if (ft_strcmp(words[0], "exit") == 0)
		return (ft_exit(words, line), 1);
	else
		return (0);
}
