/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:52:20 by ihajouji          #+#    #+#             */
/*   Updated: 2024/08/21 23:54:30 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	have_pattern(char *name, char *prefix, char *suffix)
{
	return (ft_strlen(name) >= ft_strlen(prefix) + ft_strlen(suffix)
		&& ft_strncmp(name, prefix, ft_strlen(prefix)) == 0 && ft_strcmp(name
			+ ft_strlen(name) - ft_strlen(suffix), suffix) == 0);
}

char	*finalize_results(char *results, size_t results_len)
{
	if (results_len > 0)
		results[results_len - 1] = '\0';
	else
		results[0] = '\0';
	return (results);
}
