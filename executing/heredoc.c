/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:38:40 by ihaffout          #+#    #+#             */
/*   Updated: 2024/09/13 22:47:41 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	handle_heredoc(char *limiter, char **env)
{
	char	*str;
	char	*file;
	char	*res;
	int		fd;

	file = "/tmp/heredoc";
	if (!limiter)
		return (write(2, "syntax error\n", 13), g_es = 258, -1);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open"), -1);
	handle_signals(2);
	while (1)
	{
		str = readline("> ");
		if (!str || ft_strcmp(str, limiter) == 0)
			break ;
		res = replace_env_vars_in_command(str, env);
		free(str);
		write(fd, res, ft_strlen(res));
		write(fd, "\n", 1);
		free(res);
	}
	(free(str), close(fd));
	return (open(file, O_RDONLY));
}

int	have_heredoc(t_minishell *line)
{
	int	i;

	i = 0;
	while (line->tokens[i])
	{
		if (ft_strcmp(line->tokens[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	preprocess_heredocs(t_minishell *lines, int len, char **env)
{
	int	i;
	int	fd;
	int	j;

	i = 0;
	while (i < len)
	{
		if (have_heredoc(&lines[i]))
		{
			g_es = 0;
			j = 0;
			while (j < heredoc_count(lines[i].tokens))
			{
				fd = handle_heredoc(lines[i].limiter[j], env);
				if (fd < 0)
					return (g_es = 1);
				lines[i].heredoc_fd[j++] = fd;
				if (g_es)
					return (g_es);
			}
		}
		i++;
	}
	return (0);
}
