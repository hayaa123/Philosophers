/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:08:09 by haya              #+#    #+#             */
/*   Updated: 2026/01/18 15:49:49 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int64_t *init_time_of_last(int philo_num)
{
    int64_t *time_of_last_meal;
    int i;

    time_of_last_meal = calloc(philo_num, sizeof(int64_t));
    i = 0;
    while (i < philo_num)
    {
        time_of_last_meal[i] = calc_time_now();
        if (time_of_last_meal[i] == 0)
            return (NULL);
        i++;
    }
    return (time_of_last_meal);
}

philo_t *init_philo(char **argv)
{
    philo_t *philo;

    philo = malloc(sizeof(philo_t));
    philo->philo_num = ft_atoi(argv[1]);
    philo->time_to_die = ft_atoi(argv[2]);
    philo->time_to_eat = ft_atoi(argv[3]);
    philo->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        philo->eat_count = ft_atoi(argv[5]);
    else
        philo->eat_count = 0;
    return (philo);
}

pthread_mutex_t *init_time_mutext(int philo_num)
{
    pthread_mutex_t *time_mutex;
    int i;

    time_mutex = malloc(sizeof(pthread_mutex_t) * philo_num);
    i = 0;
    if (!time_mutex)
        return (NULL);
    while (i < philo_num)
    {
        pthread_mutex_init(&(time_mutex[i]), NULL);
        i++;
    }
    return (time_mutex);
}

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

int validate_philo_data(philo_data_t *philo_data)
{
    if (!philo_data->time_mutex || !philo_data->time_of_last_meal || !philo_data->end_mutex || !philo_data->current_eat_count)
    {
        free_philo_data(philo_data);
        return (0);
    }
    return (1);
}

philo_data_t *init_philo_data(philo_t *philo)
{
    philo_data_t *philo_data;

    philo_data = malloc(sizeof(philo_data_t));
    if (!philo_data)
        return (NULL);
    philo_data->time_mutex = init_time_mutext(philo->philo_num);
    philo_data->time_of_last_meal = init_time_of_last(philo->philo_num);
    philo_data->end_mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(philo_data->end_mutex, NULL);
    philo_data->print_mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(philo_data->print_mutex, NULL);
    philo_data->current_eat_count = ft_calloc(philo->philo_num, sizeof(int));
    philo_data->end_of_simulation = 0;
    philo_data->philo = philo;
    if (validate_philo_data(philo_data) == 0)
        return (NULL);
    philo_data->start_of_simulation = calc_time_now();
    if (!philo_data->start_of_simulation)
    {
        free_philo_data(philo_data);
        return (NULL);
    }
    return (philo_data);
}

void free_all(philo_t *philo, pthread_t *philos, philo_data_t *philo_data)
{
    free(philo);
    free(philos);
    if (philo_data->current_eat_count)
        free(philo_data->current_eat_count);
    if (philo_data->time_of_last_meal)
        free(philo_data->time_of_last_meal);
    if (philo_data->print_mutex)
    {
        pthread_mutex_destroy(philo_data->print_mutex);
        free(philo_data->print_mutex);
    }
    free(philo_data);
}

pthread_mutex_t *init_forks(int philo_num)
{
    pthread_mutex_t *forks;
    int i;

    forks = malloc(philo_num * sizeof(pthread_mutex_t));
    i = 0;
    if (!forks)
        return (NULL);
    while (i < philo_num)
    {
        pthread_mutex_init(&(forks[i]), NULL);
        i++;
    }
    return (forks);
}