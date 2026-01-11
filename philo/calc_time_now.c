/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_time_now.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:07:45 by haya              #+#    #+#             */
/*   Updated: 2026/01/11 14:06:30 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int64_t calc_time_now()
{
    int64_t now;
    struct timeval timeval;

    gettimeofday(&timeval, NULL);
    now = timeval.tv_sec * 1000 + timeval.tv_usec / 1000;
    return (now); 
}