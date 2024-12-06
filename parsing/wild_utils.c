/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 09:48:00 by ihajouji          #+#    #+#             */
/*   Updated: 2024/09/08 11:25:13 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	sort_wildcards(char **res)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (res[i])
	{
		j = i + 1;
		while (res[j])
		{
			if (ft_strcmp(res[i], res[j]) > 0)
			{
				tmp = res[i];
				res[i] = res[j];
				res[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	*join_wildcards(char **res)
{
	char	*result;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (res[i])
		j += ft_strlen(res[i++]);
	result = malloc(sizeof(char) * (j + i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (res[i])
	{
		j = 0;
		while (res[i][j])
			result[k++] = res[i][j++];
		result[k++] = ' ';
		i++;
	}
	result[k] = '\0';
	return (result);
}
