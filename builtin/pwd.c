/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:25:37 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/06 13:00:33 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	ft_pwd(t_env **env)
{
	char	*pwd;

	(void)env;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_error("pwd: error retrieving current directory: \
			getcwd: failed \n", NULL);
		g_es = 1;
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	g_es = 0;
	return (0);
}
