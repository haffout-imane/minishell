/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 05:06:30 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/06 15:24:32 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	free_element(char **array)
{
	int	j;

	j = 0;
	if (array)
	{
		while (array[j])
		{
			free(array[j]);
			j++;
		}
		free(array);
	}
}

void	free_scanner(t_minishell *scanner)
{
	if (scanner->command)
		free_element(scanner->command);
	if (scanner->words)
		free_element(scanner->words);
	if (scanner->tokens)
		free_element(scanner->tokens);
	if (scanner->files)
		free_element(scanner->files);
	if (scanner->limiter)
		free_element(scanner->limiter);
	if (scanner->not_expanded)
		free_element(scanner->not_expanded);
	if (scanner->heredoc_fd)
		free(scanner->heredoc_fd);
}

void	free_minishell(t_minishell *scanner, char **new_env, char **cmnds)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (scanner)
	{
		while (scanner[i].command)
		{
			free_scanner(&scanner[i]);
			i++;
		}
		free(scanner);
	}
	while (new_env[j])
		free(new_env[j++]);
	free(new_env);
	j = 0;
	while (cmnds[j])
		free(cmnds[j++]);
	free(cmnds);
}

char	**clear_arr(char **result, int j)
{
	while (j--)
		free(result[j]);
	free(result);
	return (NULL);
}

int	_clean2(char **new_env, t_env *my_env, char **cmnds)
{
	ft_clean(new_env, my_env);
	free_element(cmnds);
	ft_error("Error\n", NULL);
	g_es = 1;
	return (1);
}
