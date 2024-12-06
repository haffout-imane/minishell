/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:33:05 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/03 07:38:40 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	add_env(t_env **my_env, char *var)
{
	t_env	*new;
	t_env	*temp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	new->var = ft_strdup(var);
	new->next = NULL;
	if (!*my_env)
	{
		*my_env = new;
		return (0);
	}
	temp = *my_env;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (0);
}

int	handle_equal_sign(char *arg, int j, t_env **my_env)
{
	char	*var;
	t_env	*temp;

	var = ft_substr(arg, 0, j);
	temp = *my_env;
	while (temp)
	{
		if (ft_strncmp(temp->var, var, j) == 0)
		{
			free(temp->var);
			temp->var = ft_strdup(arg);
			free(var);
			return (0);
		}
		temp = temp->next;
	}
	if (!temp)
	{
		if (add_env(my_env, arg) == 1)
			return (free(var), printf("error\n"), g_es = 1, 1);
	}
	free(var);
	return (0);
}

int	handle_not_equal_sign(char *arg, t_env **my_env)
{
	t_env	*temp;

	temp = *my_env;
	while (temp)
	{
		if (ft_strncmp(temp->var, arg, ft_strlen(arg)) == 0)
			return (0);
		temp = temp->next;
	}
	if (!temp)
	{
		if (add_env(my_env, arg) == 1)
			return (printf("error\n"), g_es = 1, 1);
	}
	return (0);
}

void	handle_no_var(t_env **my_env)
{
	int		j;
	t_env	*temp;

	temp = *my_env;
	while (temp)
	{
		j = 0;
		printf("declare -x ");
		while (temp->var[j] && temp->var[j] != '=')
			printf("%c", temp->var[j++]);
		if (temp->var[j] == '=')
		{
			printf("=\"");
			while (temp->var[++j])
				printf("%c", temp->var[j]);
			printf("\"\n");
		}
		else
			printf("\n");
		temp = temp->next;
	}
	return ;
}

int	ft_export(char **args, t_env **my_env)
{
	int	i;
	int	j;

	i = 0;
	if (!args[1])
		return (handle_no_var(my_env), 0);
	while (args[++i])
	{
		j = 0;
		if (check_var_name(args, i, "export"))
			return (1);
		while (args[i][j] && args[i][j] != '=')
			j++;
		if (args[i][j] == '=')
		{
			if (handle_equal_sign(args[i], j, my_env) != 0)
				return (1);
		}
		else
		{
			if (handle_not_equal_sign(args[i], my_env) != 0)
				return (1);
		}
	}
	return (0);
}
