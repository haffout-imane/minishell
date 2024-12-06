/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:05:12 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/03 12:13:41 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	contains_wildcard(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

int	is_quoted(char *token)
{
	int	i;

	i = 0;
	if (!token)
		return (0);
	while (token[i])
	{
		if (token[i] != '\\' && token[i + 1] 
			&& (token[i + 1] == '\"' || token[i + 1] == '\''))
			return (1);
		i++;
	}
	return (0);
}

char	*find_start_of_token(char *str, const char *delim)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (delim[j] != '\0')
		{
			if (str[i] == delim[j])
				break ;
			j++;
		}
		if (delim[j] == '\0')
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (NULL);
	return (&str[i]);
}

char	*find_end_of_token(char *str, const char *delim)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		if (str[i] == '\"' || str[i] == '\'')
		{
			i++;
			while (str[i] != '\0' && str[i] != '\"' && str[i] != '\'')
				i++;
			if (str[i] == '\0')
				return (NULL);
		}
		while (delim[j] != '\0')
		{
			if (str[i] == delim[j])
				return (str[i] = '\0', &str[i + 1]);
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last;
	char		*start;

	if (str != NULL)
		last = str;
	if (last == NULL)
		return (NULL);
	start = find_start_of_token(last, delim);
	if (start == NULL)
		return (last = NULL, NULL);
	last = find_end_of_token(start, delim);
	return (start);
}
