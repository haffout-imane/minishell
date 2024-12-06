/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 05:58:27 by ihaffout          #+#    #+#             */
/*   Updated: 2024/09/07 13:08:47 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	input_redirection(char *files, int *fd, int *j)
{
	*fd = open(files, O_RDONLY);
	if (*fd < 0)
		return (perror("open"), g_es = 1, g_es);
	if (dup2(*fd, STDIN_FILENO) == -1)
		return (perror("dup2"), g_es = 1, g_es);
	(*j)++;
	return (0);
}

int	output_redirection(char *files, int *fd, int *j)
{
	*fd = open(files, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd < 0)
		return (perror("open"), g_es = 1, g_es);
	if (dup2(*fd, STDOUT_FILENO) == -1)
		return (perror("dup2"), g_es = 1, g_es);
	(*j)++;
	return (0);
}

int	append_output_redirection(char *files, int *fd, int *j)
{
	*fd = open(files, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (*fd < 0)
		return (perror("open"), g_es = 1, g_es);
	if (dup2(*fd, STDOUT_FILENO) == -1)
		return (perror("dup2"), g_es = 1, g_es);
	(*j)++;
	return (0);
}

int	handle_redirections(int i, int *j, int *d, t_minishell *line)
{
	if (ft_strcmp(line->tokens[i], "<") == 0)
	{
		if (input_redirection(line->files[*j], &line->fd[*j], j) == 1)
			return (g_es);
	}
	else if (ft_strcmp(line->tokens[i], ">") == 0)
	{
		if (output_redirection(line->files[*j], &line->fd[*j], j) == 1)
			return (g_es);
	}
	else if (ft_strcmp(line->tokens[i], ">>") == 0)
	{
		if (append_output_redirection(line->files[*j], &line->fd[*j], j) == 1)
			return (g_es);
	}
	else if (ft_strcmp(line->tokens[i], "<<") == 0)
	{
		dup2(line->heredoc_fd[*d], STDIN_FILENO);
		(*d)++;
	}
	return (0);
}

int	check_tokens(t_minishell *line)
{
	int	i;
	int	j;
	int	d;
	int	count;

	i = -1;
	d = 0;
	j = 0;
	count = 0;
	if (!line->tokens || !line->tokens[0])
		return (-1);
	if (nbr_tokens(line->tokens) != nbr_files(line->files))
		return (write(STDERR_FILENO, "Error with the file\n", 20), g_es = 1, 1);
	while (line->files[count])
		count++;
	line->fd = malloc(sizeof(int) * count);
	if (!line->fd)
		return (perror("malloc"), g_es = 1, g_es);
	while (line->tokens[++i])
	{
		if (handle_redirections(i, &j, &d, line) == 1)
			return (free(line->fd), g_es);
	}
	return (free(line->fd), g_es = 0, g_es);
}
