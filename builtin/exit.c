/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:32:58 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/07 12:50:31 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	ft_atoi(char *str)
{
	unsigned long long	number;
	int					sign;
	int					i;

	sign = 1;
	i = 0;
	number = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign -= 2;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + str[i++] - 48;
		if (number > 9223372036854775807 && sign == 1)
			return (-1);
		else if (number > 9223372036854775807 && sign == -1)
			return (0);
	}
	return (number * sign);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args, t_minishell *line)
{
	if (args[1] == NULL)
		exit(line->g_es);
	else
	{
		if (is_numeric(args[1]) && args[2] == NULL)
			exit(ft_atoi(args[1]));
		else if (!is_numeric(args[1]))
		{
			printf("Error: Non-numeric argument\n");
			exit(255);
		}
		else
		{
			printf("Error: Too many arguments\n");
			g_es = 1;
			return (1);
		}
	}
}
