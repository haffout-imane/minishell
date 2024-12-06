/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihaffout <ihaffout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 22:39:23 by ihajouji          #+#    #+#             */
/*   Updated: 2024/08/21 21:20:31 by ihaffout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	init_env(t_env **my_env, char **env)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (!env || !*env)
		return ;
	while (env[i])
		i++;
	while (j < i)
	{
		ft_lstadd_back(my_env, ft_lstnew(env[j]));
		j++;
	}
}
