/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:54:58 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/01/25 14:33:38 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	safe_free(void **place)
{
	if (*place)
	{
		free(*place);
		*place = NULL;
	}
}

void	free_philo_data(t_philo_data *philo_data)
{
	int	i;

	i = 0;
	if (philo_data->time_mutex)
	{
		while (i < philo_data->philo->philo_num)
		{
			pthread_mutex_destroy(&(philo_data->time_mutex[i]));
			i++;
		}
		safe_free((void **)&(philo_data->time_mutex));
	}
	safe_free((void **)&(philo_data->time_of_last_meal));
	safe_free((void **)&(philo_data->current_eat_count));
	safe_free((void **)&(philo_data->print_mutex));
	if (philo_data->end_mutex)
	{
		pthread_mutex_destroy(philo_data->end_mutex);
		safe_free((void **)&(philo_data->end_mutex));
	}
	safe_free((void **)&(philo_data));
}

void	free_all(t_philo *philo, pthread_t *philos, t_philo_data *philo_data)
{
	if (philo_data)
		free_philo_data(philo_data);
	free(philos);
	free(philo);
}
