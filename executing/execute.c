/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:38:25 by ihaffout          #+#    #+#             */
/*   Updated: 2024/09/14 10:31:28 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	handle_child_process(t_exc *exc, t_minishell *line, int i, int *fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (exc->input_fd != STDIN_FILENO)
	{
		if (dup2(exc->input_fd, STDIN_FILENO) == -1)
			perror_exit("dup2", 1);
		close(exc->input_fd);
	}
	if (i < exc->len - 1)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			perror_exit("dup2", 1);
	}
	close(fd[0]);
	execute_command(&line[i], exc->my_env, exc->env);
	return (0);
}

int	handle_parent_process(t_exc *exc, int i, int *fd, t_minishell *line)
{
	int	j;

	j = 0;
	exc->pids[i] = exc->pid;
	close(fd[1]);
	if (exc->input_fd != STDIN_FILENO)
		close(exc->input_fd);
	exc->input_fd = fd[0];
	while (j < heredoc_count(line[i].tokens))
		close(line[i].heredoc_fd[j++]);
	return (0);
}

int	process_commands(t_exc *exc, t_minishell *line, int *fd)
{
	int	i;

	i = 0;
	while (i < exc->len)
	{
		handle_signals(1);
		if (exc->len == 1 && check_builtin(line->words[0]))
		{
			if (check_tokens(line) == 1)
				return (g_es);
			return (is_builtin(line->words, exc->my_env, line), g_es);
		}
		if (i < exc->len - 1 && pipe(fd) == -1)
			return (perror("pipe"), 1);
		exc->pid = fork();
		if (exc->pid == -1)
			return (perror("fork"), g_es = 1, close(fd[0]),
				close (fd[1]), g_es);
		if (exc->pid == 0)
			handle_child_process(exc, line, i, fd);
		else
			handle_parent_process(exc, i, fd, line);
		i++;
	}
	return (g_es);
}

void	cleanup_resources(t_exc *exc, t_minishell *line)
{
	int	i;
	int	status;

	i = 0;
	if (exc->input_fd != STDIN_FILENO)
		close(exc->input_fd);
	while (i < exc->len)
	{
		if ((exc->len == 1 && check_builtin(line[i].words[0])))
		{
			while (line->files[i])
				close(line->fd[i++]);
			i = 0;
			while (line->limiter[i])
				close(line->heredoc_fd[i++]);
			break ;
		}
		waitpid(exc->pids[i], &status, 0);
		if (WIFEXITED(status))
			g_es = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_es = WTERMSIG(status) + 128;
		i++;
	}
	(free_element(exc->env), free(exc->pids));
}

int	execution(t_minishell *line, char **cmnds, t_env **my_env)
{
	int		fd[2];
	int		error;
	t_exc	*exc;

	error = 0;
	exc = malloc(sizeof(t_exc));
	if (!exc)
		return (g_es = 1, g_es);
	if (execution_init(exc, cmnds, my_env) == 1)
		return (cleanup_resources2(exc, line), free(exc), g_es = 1, 1);
	check_files(line, exc->len, &error);
	if (preprocess_heredocs(line, exc->len, exc->env))
		return (cleanup_resources2(exc, line), free(exc), g_es);
	if (error == 1)
		return (cleanup_resources(exc, line), free(exc), g_es = 258, g_es);
	if (process_commands(exc, line, fd) == 1)
		return (cleanup_resources(exc, line), free(exc), g_es);
	cleanup_resources(exc, line);
	free(exc);
	return (g_es);
}
