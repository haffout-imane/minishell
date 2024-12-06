/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:42:37 by ihaffout          #+#    #+#             */
/*   Updated: 2024/09/07 13:03:44 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static int	number_len(int n)
{
	int	length;

	length = 0;
	if (n == 0)
		length = 1;
	if (n < 0)
		length++;
	while (n != 0)
	{
		length++;
		n /= 10;
	}
	length++;
	return (length);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;

	len = number_len(n);
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	result = malloc(sizeof(char) * len);
	if (!result)
		return (NULL);
	if (n < 0)
	{
		result[0] = '-';
		n *= -1;
	}
	result[len - 1] = '\0';
	while (n != 0)
	{
		len--;
		result[len - 1] = n % 10 + 48;
		n /= 10;
	}
	return (result);
}

void	ft_error(char *msg, char *cmd)
{
	int	i;

	i = 0;
	if (!msg)
		return ;
	if (cmd)
	{
		write(2, "minishell: ", 11);
		while (cmd[i])
			write(2, &cmd[i++], 1);
		write(2, ": ", 2);
	}
	i = 0;
	while (msg[i])
		write(2, &msg[i++], 1);
	return ;
}

int	ft_isalnum(int c)
{
	if (((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) 
		|| c == '_' || (c >= 48 && c <= 57))
		return (1);
	return (0);
}

int	only_spaces(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
			&& str[i] != '\v' && str[i] != '\f' && str[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}
