/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 03:15:53 by ihajouji          #+#    #+#             */
/*   Updated: 2024/08/20 01:32:09 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	_handle_quote(const char *s, int i, char quote)
{
	i++;
	while (s[i] && (s[i] != quote || (i > 0 && s[i - 1] == '\\')))
		i++;
	if (s[i] == quote)
		i++;
	return (i);
}

int	skip_between_quotes(const char *s, char c, int i)
{
	while (s[i] && s[i] != c)
	{
		if (s[i] == 34 || s[i] == 39)
			i = _handle_quote(s, i, s[i]);
		else
			i++;
	}
	return (i);
}
