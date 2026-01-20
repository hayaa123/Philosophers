/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:13:26 by haya              #+#    #+#             */
/*   Updated: 2026/01/20 19:47:53 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

thread_args_t *init_thread_args(philo_t *philo, int i, pthread_mutex_t *forks, philo_data_t *philo_data)
{
    thread_args_t *args;

    args = malloc(sizeof(thread_args_t));
    if (!args)
        return (NULL);
    args->current_philo = i;
    args->current_philo_count = philo->philo_num;
    args->philo = philo;
    args->forks = forks;
    args->current_time_last = &(philo_data->time_of_last_meal[i]);
    args->current_eat_count = &(philo_data->current_eat_count[i]);
    args->end_of_simulation = &(philo_data->end_of_simulation);
    args->time_mutex = &(philo_data->time_mutex[i]);
    args->end_mutext = philo_data->end_mutex;
    args->print_mutex = philo_data->print_mutex;

    return (args);
}

void *free_args_philo(thread_args_t *args, philo_data_t *philo_data, pthread_t *philos)
{
    philo_data->end_of_simulation = 1;
    if(args)
        free(args);
    if(philos)
        free(philos);
    return (NULL);
}

pthread_t *create_philos(int philo_num, pthread_mutex_t *forks, philo_t *philo, philo_data_t *philo_data)
{
    int i;
    pthread_t *philos;
    thread_args_t *args;
    int64_t start_of_simulation;
    
    i = 0;
    philos = malloc(philo_num * sizeof(pthread_t));
    if (!philos)
        return (NULL);
    start_of_simulation = calc_time_now();
    while (i < philo_num)
    {
        args = init_thread_args(philo, i, forks, philo_data);
        if (!args)
            return (free_args_philo(args, philo_data, philos));
        args->start_of_simulation = start_of_simulation;
        if (pthread_create(&(philos[i]), NULL, &routine, (void *)args) != 0)
            return (free_args_philo(args, philo_data, philos));
        i++;
    }
    return (philos);
}

int join_philos(int philo_count, pthread_t *philos)
{
    int i;

    i = 0;
    while (i < philo_count)
    {
        if (pthread_join(philos[i], NULL) != 0)
            return (3);
        i++;
    }
    return (0);
}