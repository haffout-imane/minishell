/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:45:46 by ihaffout          #+#    #+#             */
/*   Updated: 2024/09/08 11:23:21 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

char	*handle_star_leading_wildcard(char *token)
{
	char	*pattern;
	char	*result;
	char	**res;

	pattern = token + 1;
	result = match_pattern(pattern, 1);
	res = ft_split(result, ' ');
	(free(result), sort_wildcards(res));
	result = join_wildcards(res);
	ft_free(res, 0);
	return (result);
}

char	*handle_star_trailing_wildcard(char *token)
{
	size_t	token_len;
	char	*pattern;
	char	*result;
	char	**res;

	token_len = ft_strlen(token);
	if (token_len == 0 || token[token_len - 1] != '*')
		return (ft_strdup(token));
	pattern = malloc(token_len);
	if (!pattern)
		return (NULL);
	ft_strncpy(pattern, token, token_len - 1);
	pattern[token_len - 1] = '\0';
	result = match_pattern(pattern, 2);
	free(pattern);
	res = ft_split(result, ' ');
	(free(result), sort_wildcards(res));
	result = join_wildcards(res);
	ft_free(res, 0);
	return (result);
}

char	*handle_star_leading_trailing_wildcard(char *token)
{
	char	*pattern;
	char	*result;
	int		i;
	char	**res;

	i = 1;
	pattern = malloc(ft_strlen(token) - 1);
	if (!pattern)
		return (NULL);
	while (token[i] != '*')
	{
		pattern[i - 1] = token[i];
		i++;
	}
	pattern[i - 1] = '\0';
	result = match_pattern(pattern, 3);
	free(pattern);
	res = ft_split(result, ' ');
	(free(result), sort_wildcards(res));
	result = join_wildcards(res);
	ft_free(res, 0);
	return (result);
}

char	*handle_only_star_wildcard(void)
{
	DIR		*dir;
	char	*results;
	int		results_len;
	char	**res;

	results_len = 0;
	results = malloc(INITIAL_BUFFER_SIZE);
	if (!results)
		return (NULL);
	results[0] = '\0';
	dir = opendir(".");
	if (!dir)
		return (perror("opendir"), free(results), NULL);
	results = collect_files(dir, results, &results_len);
	if (results_len > 0)
		results[results_len - 1] = '\0';
	else
		results[0] = '\0';
	res = ft_split(results, ' ');
	(free(results), sort_wildcards(res));
	results = join_wildcards(res);
	(ft_free(res, 0), closedir(dir));
	return (results);
}

char	*handle_wildcards(char *command)
{
	char	*expanded_command;
	char	*token;
	size_t	len;

	len = 0;
	expanded_command = init_expanded_command();
	if (!expanded_command)
		return (NULL);
	while (command[len] == ' ')
		len++;
	if (command[len] == '\0')
		return (free(expanded_command), ft_strdup(command));
	token = ft_strtok(command, " ");
	while (token != NULL)
	{
		process_token(expanded_command, token);
		token = ft_strtok(NULL, " ");
	}
	len = ft_strlen(expanded_command);
	if (len > 0)
		expanded_command[len - 1] = '\0';
	return (expanded_command);
}
