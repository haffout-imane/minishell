/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 06:38:16 by ihajouji          #+#    #+#             */
/*   Updated: 2024/08/22 04:48:10 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	skip_leading_delimiters(char *s, int i, char c)
{
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

int	is_double_redirection(char *str, int i)
{
	return ((str[i + 1] && str[i] == '>' && str[i + 1] == '>') || (str[i + 1]
			&& str[i] == '<' && str[i + 1] == '<'));
}

int	is_redirection(char c)
{
	return (c == '>' || c == '<');
}

int	handle_quote(char *s, int i, char quote)
{
	i++;
	while (s[i] && (s[i] != quote || (i > 0 && s[i - 1] == '\\')))
		i++;
	if (s[i] == quote)
		i++;
	return (i);
}

int	ft_skip(char *str, int i, char c)
{
	while (str[i] && str[i] != c && !is_redirection(str[i]))
	{
		if (str[i] == '"' || str[i] == '\'')
			i = handle_quote(str, i, str[i]);
		else
			i++;
	}
	return (i);
}
