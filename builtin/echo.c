/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 04:33:18 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/07 12:27:58 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	check_option(char **args, int *flag)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (args[i][j] == '-' && args[i][j + 1] == 'n')
		{
			j++;
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] == '\0')
			{
				*flag = 0;
				i++;
				continue ;
			}
			else
				break ;
		}
		else
			break ;
	}
	return (i);
}

int	ft_echo(char **args)
{
	int	i;
	int	nl;

	nl = 1;
	i = check_option(args, &nl);
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	return (g_es = 0, 0);
}
