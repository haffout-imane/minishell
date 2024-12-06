/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:32:41 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/01 11:38:55 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

char	*match_pattern(char *pattern, int position)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*results;
	size_t			res_len;

	dir = open_directory_and_init_results(&results, &res_len);
	if (!dir)
		return (NULL);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (check_dote(entry->d_name) && ft_strncmp(pattern, ".", 1) != 0)
			continue ;
		if (handle_position(position, pattern, entry->d_name) == 1)
		{
			results = append_to_results2(results, &res_len, entry->d_name, dir);
			if (!results)
				return (NULL);
		}
	}
	closedir(dir);
	results = finalize_results(results, res_len);
	return (results);
}

char	*collect_files(DIR *dir, char *results, int *results_len)
{
	struct dirent	*entry;
	char			*tmp;

	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (entry->d_name[0] == '.')
			continue ;
		if ((*results_len) + ft_strlen(entry->d_name) + 2 > INITIAL_BUFFER_SIZE)
		{
			tmp = malloc((*results_len) + ft_strlen(entry->d_name) + 2);
			if (!tmp)
				return (free(results), closedir(dir), NULL);
			ft_strcat(tmp, results);
			free(results);
			results = tmp;
		}
		ft_strcat(results, entry->d_name);
		ft_strcat(results, " ");
		(*results_len) += ft_strlen(entry->d_name) + 1;
	}
	return (results);
}

char	*expand_wildcards(char *token)
{
	char	*result;

	if (contains_wildcard(token))
	{
		if (token[0] == '*' && token[1] == '\0')
			result = handle_only_star_wildcard();
		else if (token[0] == '*' && token[ft_strlen(token) - 1] == '*')
			result = handle_star_leading_trailing_wildcard(token);
		else if (token[0] == '*' && token[1] != '\0' 
			&& !contains_wildcard(token + 1))
			result = handle_star_leading_wildcard(token);
		else if (token[ft_strlen(token) - 1] == '*')
			result = handle_star_trailing_wildcard(token);
		else
			result = handle_star_middle_wildcard(token);
		if (result && ft_strlen(result) == 0)
		{
			free(result);
			return (ft_strdup(token));
		}
		return (result);
	}
	return (ft_strdup(token));
}

char	*init_expanded_command(void)
{
	char	*expanded_command;

	expanded_command = malloc(INITIAL_BUFFER_SIZE);
	if (!expanded_command)
		return (NULL);
	expanded_command[0] = '\0';
	return (expanded_command);
}

void	process_token(char *expanded_command, char *token)
{
	char	*expanded_token;

	if (contains_wildcard(token) && !is_quoted(token))
	{
		expanded_token = expand_wildcards(token);
		if (expanded_token)
		{
			ft_strcat(expanded_command, expanded_token);
			free(expanded_token);
		}
	}
	else
		ft_strcat(expanded_command, token);
	ft_strcat(expanded_command, " ");
}
