/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:04:34 by ihajouji          #+#    #+#             */
/*   Updated: 2024/08/21 23:54:20 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

char	*ft_realloc(char *results, int size, DIR *dir)
{
	char	*tmp;

	tmp = malloc(size);
	if (!tmp)
	{
		free(results);
		closedir(dir);
		return (NULL);
	}
	ft_strcat(tmp, results);
	free(results);
	results = tmp;
	return (results);
}

int	check_dote(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '.' && str[1] == '\0')
		return (1);
	if (str[0] == '.' && str[1] == '.' && str[2] == '\0')
		return (1);
	return (0);
}

char	*append_to_results2(char *res, size_t *res_len, char *name, DIR *dir)
{
	int	entry_len;

	entry_len = ft_strlen(name);
	if (*res_len + entry_len + 2 > INITIAL_BUFFER_SIZE)
	{
		res = ft_realloc(res, *res_len + entry_len + 2, dir);
		if (!res)
			return (NULL);
	}
	ft_strcat(res, name);
	ft_strcat(res, " ");
	*res_len += entry_len + 1;
	return (res);
}

int	handle_position(int position, char *pattern, char *entry_name)
{
	size_t	pattern_len;
	size_t	entry_len;

	if (position == 1)
	{
		entry_len = ft_strlen(entry_name);
		pattern_len = ft_strlen(pattern);
		if (entry_len >= pattern_len && ft_strcmp(entry_name + entry_len
				- pattern_len, pattern) == 0)
			return (1);
	}
	else if (position == 2)
	{
		if (ft_strncmp(entry_name, pattern, ft_strlen(pattern)) == 0)
			return (1);
	}
	else if (position == 3)
	{
		if (ft_strstr(entry_name, pattern) != NULL)
			return (1);
	}
	return (0);
}
