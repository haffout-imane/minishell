/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:39:42 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/01 10:06:38 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	ft_env(t_env **env)
{
	t_env	*temp;

	temp = *env;
	if (!temp)
		return (g_es = 1, 1);
	while (temp)
	{
		if (ft_strstr(temp->var, "="))
			printf("%s\n", temp->var);
		temp = temp->next;
	}
	return (g_es = 0, 0);
}
