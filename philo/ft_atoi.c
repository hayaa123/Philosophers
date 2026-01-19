/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:14:22 by haya              #+#    #+#             */
/*   Updated: 2026/01/19 10:49:41 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_atoi(const char *nptr)
{
	int	i;
	int	num;
	int	sign;

	i = 0;
	num = 0;
	sign = 1;
	while (isspace(nptr[i]) == 1)
	{
		i = i + 1;
	}
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
		{
			sign = sign * -1;
		}
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = 10 * num + (nptr[i] - '0');
		i++;
	}
	return (sign * num);
}
