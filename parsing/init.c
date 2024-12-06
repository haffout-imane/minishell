/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 03:54:29 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/08 10:04:28 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	init_var(t_var *var)
{
	var->c_index = 0;
	var->t_index = 0;
	var->w_index = 0;
	var->f_index = 0;
	var->l_index = 0;
}

t_minishell	*fill_struct(t_minishell *scanner, int i)
{
	t_var	var;

	init_var(&var);
	while (scanner[i].command[var.c_index])
	{
		if (is_redirection_(scanner[i].command[var.c_index]) == 0
			|| is_heredoc(scanner[i].command[var.c_index]) == 0)
		{
			if (handle_redirection_heredoc(&scanner[i], &var))
				return (g_es = 1, NULL);
		}
		else
		{
			if (fill_words(&scanner[i], &var))
				return (g_es = 1, NULL);
		}
	}
	scanner[i].words[var.w_index] = NULL;
	scanner[i].tokens[var.t_index] = NULL;
	scanner[i].files[var.f_index] = NULL;
	scanner[i].limiter[var.l_index] = NULL;
	return (scanner);
}

char	*handle_env_var_wild(char *command, char **env)
{
	char	*result;
	char	*tmp;

	tmp = replace_env_vars_in_command(command, env);
	if (!tmp)
		return (g_es = 1, NULL);
	result = handle_wildcards(tmp);
	free(tmp);
	return (result);
}

t_minishell	*allocate_scanner(t_minishell *scanner, int i)
{
	scanner[i].words = malloc(sizeof(char *) * (word_count(scanner[i].command)
				+ 1));
	scanner[i].tokens = malloc(sizeof(char *) * (token_count(scanner[i].command)
				+ 1));
	scanner[i].files = malloc(sizeof(char *) * (token_count(scanner[i].command)
				+ 1));
	scanner[i].limiter = malloc(sizeof(char *)
			* heredoc_count(scanner[i].command) + 1);
	scanner[i].heredoc_fd = malloc(sizeof(int)
			* heredoc_count(scanner[i].command) + 1);
	if (!scanner[i].words || !scanner[i].tokens || !scanner[i].files
		|| !scanner[i].limiter)
		return (g_es = 1, NULL);
	return (scanner);
}

t_minishell	*init_structs(char **cmnds, char **env)
{
	int			i;
	t_minishell	*scanner;
	char		*processed_command;

	i = 0;
	scanner = malloc(sizeof(t_minishell) * (count_commands(cmnds) + 1));
	if (!scanner)
		return (g_es = 1, NULL);
	while (cmnds[i])
	{
		scanner = init_scanner(scanner, i, cmnds[i]);
		processed_command = handle_env_var_wild(cmnds[i], env);
		scanner[i].command = ft_split(processed_command, ' ');
		free(processed_command);
		if (!scanner[i].command)
			return (g_es = 1, NULL);
		scanner = allocate_scanner(scanner, i);
		if (scanner)
			scanner = fill_struct(scanner, i);
		if (!scanner)
			return (g_es = 1, NULL);
		i++;
	}
	scanner[i].command = NULL;
	return (scanner);
}
