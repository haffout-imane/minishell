/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:31:57 by ihajouji          #+#    #+#             */
/*   Updated: 2024/08/24 17:06:47 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

char	*process_redirection(char *s, int start, int *i)
{
	if ((s[*i + 1] && s[*i] == '>' && s[*i + 1] == '>') || (s[*i + 1]
			&& s[*i] == '<' && s[*i + 1] == '<'))
	{
		*i += 2;
		return (fill(s, start, *i));
	}
	else
	{
		++(*i);
		return (fill(s, start, *i));
	}
}

char	*process_text(char *s, int start, int *i, char c)
{
	*i = ft_skip(s, *i, c);
	return (fill(s, start, *i));
}

char	**process_string(char *s, char c, char **result)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		i = skip_leading_delimiters(s, i, c);
		if (s[i])
		{
			start = i;
			if (is_redirection(s[i]))
				result[j] = process_redirection(s, start, &i);
			else
				result[j] = process_text(s, start, &i, c);
			if (!result[j])
				return (clear_arr(result, j));
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}

int	string_count(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		i = skip_leading_delimiters(str, i, c);
		if (str[i])
		{
			count++;
			if (str[i] == '"' || str[i] == '\'')
				i = handle_quote(str, i, str[i]);
			else if (is_redirection(str[i]))
			{
				if (is_double_redirection(str, i))
					i++;
				i++;
				count++;
			}
			else
				i = ft_skip(str, i, c);
		}
	}
	return (count);
}

char	**ft_split(char *s, char c)
{
	char	**result;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] == c)
		i++;
	if (!s[i])
	{
		result = malloc(sizeof(char *) + 1);
		if (!result)
			return (NULL);
		result[0] = ft_strdup(s);
		result[1] = NULL;
		return (result);
	}
	result = malloc(sizeof(char *) * (string_count(s, c) + 1));
	if (!result)
		return (NULL);
	result = process_string(s, c, result);
	return (result);
}
