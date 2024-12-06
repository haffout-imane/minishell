/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 06:44:08 by ihajouji          #+#    #+#             */
/*   Updated: 2024/08/25 05:39:42 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	is_escaped(char *str, int i, char quote)
{
	return (str[i] == '\\' && (str[i + 1] == quote || str[i + 1] == '\\'));
}

void	handle_escaped_characters(char *str, int *i, char *result, int *j)
{
	if (str[*i] == '\\' && (str[*i + 1] == '"' || str[*i + 1] == '\'' 
			|| str[*i + 1] == '\\'))
		(*i)++;
	result[(*j)++] = str[(*i)++];
}

void	copy_characters(char *str, int start, int end, char *result)
{
	int		i;
	int		j;
	char	quote;

	i = start;
	j = 0;
	while (i < end)
	{
		if ((str[i] == '"' || str[i] == '\'') && (i == start 
				|| str[i - 1] != '\\'))
		{
			quote = str[i++];
			while (i < end && (str[i] != quote || str[i - 1] == '\\'))
			{
				if (is_escaped(str, i, quote))
					i++;
				result[j++] = str[i++];
			}
			if (i < end && str[i] == quote)
				i++;
		}
		else
			handle_escaped_characters(str, &i, result, &j);
	}
	result[j] = '\0';
}

char	*fill(char *str, int start, int end)
{
	char	*result;

	result = malloc(sizeof(char) * (end - start + 1));
	if (!result)
		return (NULL);
	copy_characters(str, start, end, result);
	return (result);
}
