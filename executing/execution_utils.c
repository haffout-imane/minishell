/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:44:53 by ihaffout          #+#    #+#             */
/*   Updated: 2024/09/14 17:21:50 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	cleanup_resources2(t_exc *exc, t_minishell *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < exc->len)
	{
		j = 0;
		if (!line[i].limiter[0])
			i++;
		else
		{
			while (line[i].limiter[j])
				close(line[i].heredoc_fd[j++]);
			i++;
		}
	}
	if (exc->input_fd != STDIN_FILENO)
		close(exc->input_fd);
	i = 0;
	while (exc->env[i])
		free(exc->env[i++]);
	free(exc->env);
	free(exc->pids);
}

void	perror_exit(char *str, int nbr)
{
	perror(str);
	g_es = nbr;
	exit(g_es);
}

int	execution_init(t_exc *exc, char **cmnds, t_env **my_env)
{
	exc->input_fd = STDIN_FILENO;
	exc->len = 0;
	while (cmnds[exc->len])
		exc->len++;
	exc->pids = malloc(sizeof(pid_t) * exc->len);
	if (!exc->pids)
		return (perror("malloc"), 1);
	exc->env = replace_new_env(*my_env);
	exc->my_env = my_env;
	return (0);
}

void	check_valid(t_minishell *line)
{
	struct stat	path_stat;

	if (!line->words[0])
		exit(0);
	if ((line->words[0][ft_strlen(line->words[0]) - 1] == '/')
		|| line->words[0][0] == '/')
	{
		if (stat(line->words[0], &path_stat) == -1)
		{
			ft_error("No such file or directory\n", line->words[0]);
			g_es = 127;
			exit(127);
		}
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_error("is a directory\n", line->words[0]);
			g_es = 126;
			exit(126);
		}
	}
	return ;
}

void	execute_command(t_minishell *line, t_env **my_env, char **env)
{
	char	*path;

	if (only_spaces(line->words[0]))
		exit(g_es);
	if (check_tokens(line) == 1)
		exit(g_es);
	if (!is_builtin(line->words, my_env, line))
	{
		check_valid(line);
		path = get_path(line->words[0], env);
		if (!path && access(line->words[0], F_OK) == 0)
			path = ft_strdup(line->words[0]);
		if (!path)
		{
			ft_error("Command not found\n", line->words[0]);
			g_es = 127;
			exit(127);
		}
		if (execve(path, line->words, env) == -1)
			perror_exit("execve", 127);
	}
	exit(0);
}
