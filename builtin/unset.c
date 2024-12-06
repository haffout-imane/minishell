/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:33:15 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/07 12:24:41 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	var_name_length(char *var)
{
	int	i;

	if (!var)
		return (0);
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

void	remove_node(t_env **my_env, t_env *node_to_remove)
{
	t_env	*temp;
	t_env	*prev;

	temp = *my_env;
	prev = NULL;
	while (temp)
	{
		if (temp == node_to_remove)
		{
			if (prev)
				prev->next = temp->next;
			else
				*my_env = temp->next;
			free(temp->var);
			free(temp);
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
}

int	ft_unset(char **words, t_env **my_env)
{
	t_env	*temp;
	t_env	*prev;
	int		i;
	int		j;

	i = 1;
	if (!*my_env || !my_env)
		return (printf("Error\n"), g_es = 1, 1);
	if (check_var_name(words, i, "unset"))
		return (1);
	while (words[i])
	{
		temp = *my_env;
		prev = NULL;
		while (temp)
		{
			j = var_name_length(temp->var);
			if (ft_strncmp(temp->var, words[i], j) == 0)
				remove_node(my_env, temp);
			prev = temp;
			temp = temp->next;
		}
		i++;
	}
	return (0);
}
