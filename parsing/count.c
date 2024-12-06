/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 04:07:44 by ihajouji          #+#    #+#             */
/*   Updated: 2024/08/27 19:44:27 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	count_commands(char **cmnds)
{
	int	count;

	count = 0;
	while (cmnds[count])
		count++;
	return (count);
}

int	heredoc_count(char **str)
{
	int	count;

	count = 0;
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (ft_strcmp(*str, "<<") == 0)
			count++;
		str++;
	}
	return (count);
}

int	token_count(char **str)
{
	int	count;

	count = 0;
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (ft_strcmp(*str, ">>") == 0 || ft_strcmp(*str, "<<") == 0
			|| ft_strcmp(*str, ">") == 0 || ft_strcmp(*str, "<") == 0)
			count++;
		str++;
	}
	return (count);
}

int	word_count(char **str)
{
	int	count;

	count = 0;
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (ft_strcmp(*str, ">>") != 0 && ft_strcmp(*str, "<<") != 0
			&& ft_strcmp(*str, ">") != 0 && ft_strcmp(*str, "<") != 0)
			count++;
		str++;
	}
	return (count);
}
