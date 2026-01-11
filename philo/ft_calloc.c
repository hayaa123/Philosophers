/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:08:15 by haya              #+#    #+#             */
/*   Updated: 2026/01/11 14:14:43 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *ft_calloc(int count, unsigned long size)
{
    int *out;
    int i;

    out = malloc(count * size);
    i = 0;
    while(i < count)
    {
        out[i] = 0;
        i++;
    }
    return (out);
}