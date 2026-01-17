/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:13:26 by haya              #+#    #+#             */
/*   Updated: 2026/01/17 17:10:13 by haya             ###   ########.fr       */
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
    args->start_of_simulation = philo_data->start_of_simulation;
    return (args);
}

pthread_t *create_philos(int philo_num, pthread_mutex_t *forks, philo_t *philo, philo_data_t *philo_data)
{
    int i;
    pthread_t *philos;
    thread_args_t *args;

    i = 0;
    philos = malloc(philo_num * sizeof(pthread_t));
    if (!philos)
        return (NULL);
    while (i < philo_num)
    {
        args = init_thread_args(philo, i, forks, philo_data);
        if (!args)
        {
            philo_data->end_of_simulation = 1;
            free(philos);
            return (NULL);
        }
        if (pthread_create(&(philos[i]), NULL, &routine, (void *)args) != 0)
        {
            free(args);
            free(philos);
            return (NULL);
        }
        usleep(10000 * i); // is this correct ?
                           // this solved the problem of dieing philo in the test ./philo 5 800 200 200
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