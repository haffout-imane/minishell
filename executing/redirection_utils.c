/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihaffout <ihaffout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:41:03 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/05 09:43:46 by ihaffout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	nbr_files(char **files)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (!files || !files[0])
		return (0);
	while (files[i])
	{
		if (ft_strcmp(files[i], "\n") == 0)
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

int	nbr_tokens(char **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!tokens || !tokens[0])
		return (0);
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "<<") != 0)
			count++;
		i++;
	}
	return (count);
}

void	check_files(t_minishell *line, int len, int *error)
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (line[i].files[j])
		{
			if (ft_strcmp(line[i].files[j], "<") == 0 
				|| ft_strcmp(line[i].files[j], ">") == 0 
				|| ft_strcmp(line[i].files[j], ">>") == 0 
				|| ft_strcmp(line[i].files[j], "<<") == 0)
			{
				write(2, "minishell: syntax error\n", 24);
				*error = 1;
				return ;
			}
			j++;
		}
		i++;
	}
	return ;
}
