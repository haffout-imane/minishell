/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:02:34 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/08 11:20:22 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

char	*append_to_results(char *results, size_t *results_len, char *entry_name)
{
	char	*tmp;
	size_t	entry_len;

	entry_len = ft_strlen(entry_name);
	if (*results_len + entry_len + 2 > INITIAL_BUFFER_SIZE)
	{
		tmp = malloc(*results_len + entry_len + 2);
		if (!tmp)
		{
			free(results);
			return (NULL);
		}
		ft_strcpy(tmp, results);
		free(results);
		results = tmp;
	}
	ft_strcat(results, entry_name);
	ft_strcat(results, " ");
	*results_len += entry_len + 1;
	return (results);
}

DIR	*open_directory_and_init_results(char **results, size_t *results_len)
{
	DIR	*dir;

	*results_len = 0;
	*results = malloc(INITIAL_BUFFER_SIZE);
	if (!*results)
		return (NULL);
	(*results)[0] = '\0';
	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		free(*results);
		return (NULL);
	}
	return (dir);
}

char	*match_pattern_with_prefix_suffix(char *prefix, char *suffix)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*results;
	size_t			results_len;

	dir = open_directory_and_init_results(&results, &results_len);
	if (!dir)
		return (NULL);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (check_dote(entry->d_name))
			continue ;
		if (have_pattern(entry->d_name, prefix, suffix))
		{
			results = append_to_results(results, &results_len, entry->d_name);
			if (!results)
				return (closedir(dir), NULL);
		}
	}
	closedir(dir);
	results = finalize_results(results, results_len);
	return (results);
}

void	extract_prefix_suffix(char *token, char **prefix, char **suffix)
{
	char	*token_copy;

	if (token[0] == '*')
		token++;
	token_copy = ft_strdup(token);
	if (!token_copy)
		return ;
	*prefix = ft_strtok(token_copy, "*");
	*suffix = ft_strtok(NULL, "*");
	free(token_copy);
}

char	*handle_star_middle_wildcard(char *token)
{
	char	*original_token;
	char	*results;
	char	*matched_part;
	char	*prefix;
	char	*suffix;

	original_token = ft_strdup(token);
	if (!original_token)
		return (NULL);
	extract_prefix_suffix(token, &prefix, &suffix);
	if (prefix && suffix)
	{
		matched_part = match_pattern_with_prefix_suffix(prefix, suffix);
		if (matched_part && ft_strlen(matched_part) > 0)
			results = ft_strdup(matched_part);
		else
			results = ft_strdup(original_token);
		free(matched_part);
	}
	else
		results = ft_strdup(original_token);
	return (free(original_token), results);
}
