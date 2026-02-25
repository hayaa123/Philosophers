/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_malloced_mutex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:34:08 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/01/27 10:59:44 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

pthread_mutex_t	*init_malloced_mutext(void)
{
	pthread_mutex_t	*time_mutex;

	time_mutex = malloc(sizeof(pthread_mutex_t));
	if (!time_mutex)
		return (NULL);
	pthread_mutex_init(time_mutex, NULL);
	return (time_mutex);
}
