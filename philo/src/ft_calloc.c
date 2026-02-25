/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:08:15 by haya              #+#    #+#             */
/*   Updated: 2026/01/24 11:49:01 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*ft_calloc(int count, unsigned long size)
{
	int	*out;
	int	i;

	out = malloc(count * size);
	i = 0;
	while (i < count)
	{
		out[i] = 0;
		i++;
	}
	return (out);
}
