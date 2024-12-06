/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:46:10 by ihaffout          #+#    #+#             */
/*   Updated: 2024/09/07 12:58:53 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	count_single(char **cmnds)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (cmnds[i])
	{
		j = 0;
		while (cmnds[i][j])
		{
			if ((cmnds[i][j] == '\'' && cmnds[i][j - 1] != '\\'))
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	count_double(char **cmnds)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (cmnds[i])
	{
		j = 0;
		while (cmnds[i][j])
		{
			if ((cmnds[i][j] == '\"' && cmnds[i][j - 1] != '\\'))
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	_only_spaces(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_empty(char **cmnds)
{
	int	i;

	i = 0;
	if (!cmnds)
		return (1);
	if (!cmnds[1])
		return (0);
	while (cmnds[i])
	{
		if ((only_spaces(cmnds[i]) || !cmnds[i][0]))
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_cmd(char **cmnds, char *input, char **new_env)
{
	if (input[0] == '|' || input[ft_strlen(input) - 1] == '|')
	{
		free(input);
		free_element(new_env);
		free_element(cmnds);
		return (write(2, "minishell: syntax error\n", 24), g_es = 258, 1);
	}
	if ((count_double(cmnds) % 2 != 0 || count_single(cmnds) % 2 != 0))
	{
		free(input);
		free_element(new_env);
		free_element(cmnds);
		return (write(2, "minishell: syntax error\n", 24), g_es = 258, 1);
	}
	if (check_empty(cmnds))
	{
		free(input);
		free_element(new_env);
		free_element(cmnds);
		return (write(2, "minishell: syntax error\n", 24), g_es = 258, 1);
	}
	free(input);
	return (0);
}
