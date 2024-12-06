/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:41:29 by ihaffout          #+#    #+#             */
/*   Updated: 2024/09/06 16:28:07 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"
#include <stdlib.h>
#include <unistd.h>

char	*check_absolute_path(char *command)
{
	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
	{
		if (access(command, F_OK) == 0)
			return (ft_strdup(command));
		else
		{
			ft_error("No such file or directory\n", command);
			g_es = 127;
			exit(127);
		}
	}
	return (NULL);
}

char	**get_path_variable(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	if (!env[i])
		return (NULL);
	return (ft_split(env[i] + 5, ':'));
}

char	*join_and_check_path(char *dir, char *command)
{
	char	*path;
	char	*part_path;

	part_path = ft_strjoin(dir, "/");
	path = ft_strjoin(part_path, command);
	free(part_path);
	if (access(path, F_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

char	*get_path(char *command, char **env)
{
	int		i;
	char	*result;
	char	**paths;

	i = 0;
	if (!command || !*command)
		return (NULL);
	result = check_absolute_path(command);
	if (result)
		return (result);
	paths = get_path_variable(env);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		result = join_and_check_path(paths[i], command);
		if (result)
			return (ft_free(paths, i), result);
		free(paths[i]);
		i++;
	}
	free(paths);
	return (NULL);
}

void	ft_free(char **str, int i)
{
	while (str[i])
		free(str[i++]);
	free(str);
}
