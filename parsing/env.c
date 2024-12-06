/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:00:11 by ihaffout          #+#    #+#             */
/*   Updated: 2024/09/07 12:43:49 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

char	*append_non_var_part(char *result, char *command, int start, int i)
{
	char	*temp;
	char	*new_str;

	temp = ft_substr(command, start, i - start);
	if (temp == NULL)
		return (free(result), NULL);
	new_str = ft_strjoin(result, temp);
	free(result);
	free(temp);
	return (new_str);
}

char	*replace_var(char *result, char *var_name, char **env)
{
	char	*var_value;
	char	*temp;
	char	*tmp;

	if (ft_strncmp(var_name, "?", 1) == 0)
	{
		tmp = ft_itoa(g_es);
		var_value = ft_strjoin(tmp, var_name + 1);
		free(tmp);
	}
	else
		var_value = get_variable(var_name, env);
	if (var_value)
	{
		temp = ft_strjoin(result, var_value);
		free(result);
		free(var_value);
		return (temp);
	}
	return (handle_invalid_var(result, var_name));
}

char	*process_variable(char *command, char **env, int *i, char *result)
{
	char	*var_name;

	var_name = extract_var_name(command, i);
	if (!var_name)
		return (free(result), NULL);
	result = replace_var(result, var_name, env);
	if (!result)
		return (free(var_name), NULL);
	free(var_name);
	return (result);
}

int	handle_quote_expand(char *command, int i)
{
	int	flag;

	flag = 0;
	while (command[i] && command[i] != '$')
	{
		if (command[i] == '"')
			flag = 1;
		if (command[i] == '\'' && flag == 0)
			while (command[++i] && (command[i] != '\''))
				;
		i++;
		if (command[i] == '"' && flag == 1)
			while (command[++i] && (command[i] != '"'))
				;
	}
	return (i);
}

char	*replace_env_vars_in_command(char *command, char **env)
{
	int		i;
	int		start;
	char	*result;

	i = 0;
	result = NULL;
	while (command[i])
	{
		if ((command[i] == '$' && i > 0 && command[i - 1] != '\\'))
		{
			start = ++i;
			result = process_variable(command, env, &i, result);
		}
		else if (command[0] == '$')
		{
			start = i++;
			result = process_variable(command, env, &i, result);
		}
		else
			result = handle_not_dollar(command, &i, result);
		if (!result)
			return (NULL);
	}
	g_es = 0;
	return (result);
}
