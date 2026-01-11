/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:08:09 by haya              #+#    #+#             */
/*   Updated: 2026/01/11 14:16:35 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int64_t *init_time_of_last(int philo_num)
{
    int64_t *time_of_last_meal;
    int i;
    
    time_of_last_meal = malloc(sizeof(int64_t) * philo_num);
    i = 0;
    while(i < philo_num)
    {
        time_of_last_meal[i] = calc_time_now();
        i++;
    }
    return (time_of_last_meal);
}

philo_t * init_philo(char **argv)
{
    philo_t *philo;
    
    philo = malloc(sizeof(philo_t));
    philo->philo_num = ft_atoi(argv[1]);
    philo->time_to_die = ft_atoi(argv[2]);
    philo->time_to_eat = ft_atoi(argv[3]);
    philo->time_to_sleep = ft_atoi(argv[4]);
    if(argv[5])
        philo->eat_count = ft_atoi(argv[5]);
    else
        philo->eat_count = 0;
    return (philo);
}

philo_data_t *init_philo_data(philo_t *philo)
{
    philo_data_t *philo_data;
    
    philo_data = malloc(sizeof(philo_data_t));
    philo_data->time_of_last_meal = init_time_of_last(philo->philo_num);
    philo_data->current_eat_count = ft_calloc(philo->philo_num, sizeof(int));
    philo_data->end_of_simulation = 0;
    philo_data->philo = philo;
    return (philo_data);
}

void free_all(philo_t *philo, pthread_t *philos, philo_data_t *philo_data)
{
    free(philo);
    free(philos);
    if(philo_data->current_eat_count)
        free(philo_data->current_eat_count);
    if(philo_data->time_of_last_meal)
        free(philo_data->time_of_last_meal);
    free(philo_data);
}

pthread_mutex_t *init_forks(int philo_num)
{
    pthread_mutex_t *forks;
    int i;

    forks = malloc(philo_num * sizeof(pthread_mutex_t));
    i = 0;
    if(!forks)
        return (NULL);
    while(i < philo_num)
    {
        pthread_mutex_init(&(forks[i]), NULL);
        i++;
    }
    return (forks);
}