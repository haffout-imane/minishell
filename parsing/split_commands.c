/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:37:26 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/12 11:35:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

char	*_fill(char *str, int start, int end)
{
	int		i;
	int		count;
	char	*result;

	count = end - start;
	result = malloc(sizeof(char) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < count)
	{
		result[i] = str[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}

int	_string_count(const char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
		{
			count++;
			if (str[i] == 34 || str[i] == 39)
				i = _handle_quote(str, i, str[i]);
			else
				i = skip_between_quotes(str, c, i);
		}
	}
	return (count);
}

char	**_clear_arr(char **result, int j)
{
	while (j)
		free(result[j--]);
	free(result);
	return (NULL);
}

char	**_process_string(const char *s, char c, char **result)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] && s[i] != c && (s[i] == 34 || s[i] == 39))
			i++;
		if (s[i] == 34 || s[i] == 39)
			i = _handle_quote(s, i, s[i]);
		else
			i = skip_between_quotes(s, c, i);
		result[j] = _fill((char *)s, start, i);
		if (!result[j])
			return (_clear_arr(result, j));
		j++;
	}
	return (result[j] = NULL, result);
}

char	**split_commands(const char *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc(sizeof(char *) * (_string_count(s, c) + 1));
	if (!result)
		return (NULL);
	result = _process_string(s, c, result);
	return (result);
}
