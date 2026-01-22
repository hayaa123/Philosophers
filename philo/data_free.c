/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:54:58 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/01/21 21:33:23 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void safe_free(void **place)
{
    if (*place)
    {
        free(*place);
        *place = NULL;
    }
}

void free_philo_data(philo_data_t *philo_data)
{
    int i;

    i = 0;
    while (i < philo_data->philo->philo_num)
    {
        pthread_mutex_destroy(&(philo_data->time_mutex[i]));
        i++;
    }
    safe_free((void **)&(philo_data->time_mutex));
    safe_free((void **)&(philo_data->time_of_last_meal));
    safe_free((void **)&(philo_data->current_eat_count));
    if (philo_data->end_mutex)
    {
        pthread_mutex_destroy(philo_data->end_mutex);
        safe_free((void **)&(philo_data->end_mutex));
    }
    safe_free((void **)&(philo_data));
}

void free_all(philo_t *philo, pthread_t *philos, philo_data_t *philo_data)
{
    free(philo);
    free(philos);
    if (philo_data->current_eat_count)
        free(philo_data->current_eat_count);
    if (philo_data->time_of_last_meal)
        free(philo_data->time_of_last_meal);
    if(philo_data->time_mutex)
    {
        pthread_mutex_destroy(philo_data->time_mutex);
        free(philo_data->time_mutex);
    }
    if (philo_data->print_mutex)
    {
        pthread_mutex_destroy(philo_data->print_mutex);
        free(philo_data->print_mutex);
    }
    if(philo_data->end_mutex)
        free(philo_data->end_mutex);
    free(philo_data);
}
