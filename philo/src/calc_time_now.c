/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_time_now.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:07:45 by haya              #+#    #+#             */
/*   Updated: 2026/01/24 11:51:34 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int64_t	calc_time_now(void)
{
	int64_t			now;
	struct timeval	timeval;

	if (gettimeofday(&timeval, NULL) == -1)
		return (0);
	now = timeval.tv_sec * 1000 + timeval.tv_usec / 1000;
	return (now);
}
