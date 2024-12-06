/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:51:56 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/07 12:52:33 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	is_redirection_(char *str)
{
	if (ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">") == 0 
		|| ft_strcmp(str, ">>") == 0)
		return (0);
	return (1);
}

int	is_heredoc(char *str)
{
	if (ft_strcmp(str, "<<") == 0)
		return (0);
	return (1);
}

t_minishell	*init_scanner(t_minishell *scanner, int i, char *cmnd)
{
	scanner[i].command = NULL;
	scanner[i].words = NULL;
	scanner[i].tokens = NULL;
	scanner[i].files = NULL;
	scanner[i].limiter = NULL;
	scanner[i].heredoc_fd = STDIN_FILENO;
	scanner[i].not_expanded = ft_split(cmnd, ' ');
	scanner[i].g_es = g_es;
	return (scanner);
}

int	fill_words(t_minishell *scnr, t_var *var)
{
	scnr->words[(var->w_index)++] = ft_strdup(scnr->command[(var->c_index)++]);
	if (!scnr->words[var->w_index - 1])
		return (1);
	return (0);
}

int	handle_redirection_heredoc(t_minishell *scnr, t_var *var)
{
	if (is_redirection_(scnr->command[var->c_index]) == 0)
	{
		scnr->tokens[(var->t_index)++] = ft_strdup(
				scnr->command[(var->c_index)++]);
		if (scnr->command[var->c_index])
			scnr->files[(var->f_index)++] = ft_strdup(
					scnr->command[(var->c_index)++]);
		else
			scnr->files[(var->f_index)++] = ft_strdup("\n");
		if (!scnr->tokens[var->t_index - 1] || !scnr->files[var->f_index - 1])
			return (1);
	}
	else if (is_heredoc(scnr->command[var->c_index]) == 0)
	{
		scnr->tokens[(var->t_index)++] = ft_strdup(
				scnr->command[(var->c_index)++]);
		if (!scnr->command[var->c_index])
			return (0);
		scnr->limiter[(var->l_index)++] = ft_strdup(
				scnr->not_expanded[(var->c_index)++]);
		if (!scnr->limiter[var->l_index - 1] 
			|| !scnr->tokens[var->t_index - 1])
			return (1);
	}
	return (0);
}
