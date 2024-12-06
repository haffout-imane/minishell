/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:04:34 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/07 09:32:16 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

char	*extract_var_name(char *command, int *i)
{
	int		start;
	char	*temp;

	temp = NULL;
	start = *i;
	while (command[*i] && (ft_isalnum(command[*i]) == 1 || (command[*i] == '?'))
		&& command[*i] != '$')
	{
		if (command[start] >= 48 && command[start] <= 57)
			return (ft_strdup(""));
		(*i)++;
	}
	if (start == *i)
	{
		(*i)++;
		if (command[start + 1])
			temp = append_space(command, start);
		else
			temp = ft_strdup("$");
		return (temp);
	}
	return (ft_substr(command, start, *i - start));
}

char	*get_variable(char *word, char **env)
{
	int		i;
	size_t	word_len;
	char	*tmp;

	i = 0;
	if (ft_strcmp(word, "$") == 0 || ft_strcmp(word, "$ ") == 0)
		return (ft_strdup(word));
	word_len = ft_strlen(word);
	tmp = ft_strjoin(word, "=");
	if (!tmp)
		return (NULL);
	while (env[i])
	{
		if (ft_strnstr(env[i], tmp, word_len + 1) == env[i])
		{
			free(tmp);
			return (ft_strdup(env[i] + word_len + 1));
		}
		i++;
	}
	free(tmp);
	return (NULL);
}

char	*ft_strndup(char *s, int n)
{
	char	*dup;
	int		len;
	int		i;

	if (s == NULL)
		return (NULL);
	len = 0;
	while (s[len] && len < n)
		len++;
	dup = malloc(len + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

char	*handle_invalid_var(char *result, char *var_name)
{
	char	*temp;

	var_name = NULL;
	temp = ft_strjoin(result, var_name);
	free(result);
	free(var_name);
	return (temp);
}

char	*handle_not_dollar(char *command, int *i, char *result)
{
	int	start;

	start = *i;
	if (((command[(*i)] >= '0' && command[(*i)] <= '9') || command[(*i)] == '@')
		&& command[(*i) - 1] == '$')
		start++;
	*i = handle_quote_expand(command, *i);
	if (command[(*i)] == '$' && command[(*i) + 1] == '\0')
		(*i)++;
	result = append_non_var_part(result, command, start, *i);
	return (result);
}
