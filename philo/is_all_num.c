/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_all_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:53:16 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/01/24 12:09:42 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n')
	{
		return (1);
	}
	if (c == '\r' || c == '\t' || c == '\v')
	{
		return (1);
	}
	return (0);
}

static void	skip_spaces(char *str, int *i, int *j)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (isspace(str[*i]))
			(*i)++;
		if (isspace(str[*j]))
			(*j)--;
		if (i == j)
			break ;
		index++;
	}
}

int	is_all_num(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(str) - 1;
	skip_spaces(str, &i, &j);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (i <= j)
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}
