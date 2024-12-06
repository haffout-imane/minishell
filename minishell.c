/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 06:30:41 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/12 11:30:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_es = 0;

void	ft_clean(char **new_env, t_env *my_env)
{
	int	i;

	i = 0;
	ft_free(new_env, 0);
	while (my_env)
	{
		free(my_env->var);
		free(my_env);
		my_env = my_env->next;
	}
}

int	_clean(char **new_env, t_env *my_env, char *input)
{
	ft_clean(new_env, my_env);
	free(input);
	ft_error("Error\n", NULL);
	g_es = 1;
	return (1);
}

char	**replace_new_env(t_env *my_env)
{
	t_env	*temp;
	char	**new_env;
	int		i;

	i = 0;
	temp = my_env;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	temp = my_env;
	while (temp)
	{
		new_env[i] = ft_strdup(temp->var);
		i++;
		temp = temp->next;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	minishell(int clone_stdin, int clone_stdout, t_env *my_env)
{
	char		*input;
	char		**cmnds;
	t_minishell	*scanner;
	char		**new_env;

	while (1)
	{
		handle_signals(0);
		new_env = replace_new_env(my_env);
		input = read_input(new_env);
		if (input == NULL)
			return (ft_clean(new_env, my_env), g_es = 0, 0);
		cmnds = split_commands(input, '|');
		if (!cmnds)
			return (_clean(new_env, my_env, input));
		if (check_valid_cmd(cmnds, input, new_env) == 1)
			continue ;
		scanner = init_structs(cmnds, new_env);
		if (!scanner)
			return (_clean2(new_env, my_env, cmnds));
		execution(scanner, cmnds, &my_env);
		free_minishell(scanner, new_env, cmnds);
		(dup2(clone_stdin, STDIN_FILENO), dup2(clone_stdout, STDOUT_FILENO));
	}
	return (g_es = 0, 0);
}

int	main(int ac, char **av, char **env)
{
	t_env		*my_env;
	int			clone_stdin;
	int			clone_stdout;

	my_env = NULL;
	(void)av;
	if (ac > 1)
		return (ft_error("you must not enter an argument\n", NULL), 1);
	clone_stdin = dup(STDIN_FILENO);
	clone_stdout = dup(STDOUT_FILENO);
	init_env(&my_env, env);
	minishell(clone_stdin, clone_stdout, my_env);
	close(clone_stdin);
	close(clone_stdout);
	return (g_es);
}
