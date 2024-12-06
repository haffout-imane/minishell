/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:04:30 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/14 09:41:44 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	check_var_name(char **args, int i, char *name)
{
	int	j;

	j = 0;
	if (!args[i])
		return (1);
	if ((args[i][0] >= '0' && args[i][0] <= '9') || args[i][0] == '=')
		return (printf("minishell: %s: `%s': not a valid identifier\n", name, \
			args[i]), g_es = 1, 1);
	while (args[i][j] && args[i][j] != '=')
	{
		if (!ft_isalnum(args[i][j]))
			return (printf("minishell: %s: `%s': not a valid identifier\n", \
				name, args[i]), g_es = 1, 1);
		j++;
	}
	return (0);
}
