/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 03:51:57 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/07 09:33:43 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (1);
		else if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (-1);
		i++;
	}
	return (0);
}

char	*read_input(char **env)
{
	int		i;
	char	*prompt;
	char	*line;

	i = 0;
	while (env[i] && ft_strnstr(env[i], "USER=", 5) == 0)
		i++;
	if (!env[i])
		prompt = ft_strdup("$ ");
	else
		prompt = ft_strjoin(env[i] + 5, " $ ");
	line = readline(prompt);
	free(prompt);
	if (line && *line)
		add_history(line);
	return (line);
}

char	*append_space(char *command, int start)
{
	char	*tmp;
	char	*result;

	tmp = ft_strndup(command + start, 1);
	if (!tmp)
		return (NULL);
	result = ft_strjoin("$", tmp);
	free(tmp);
	if (!result)
		return (NULL);
	return (result);
}
