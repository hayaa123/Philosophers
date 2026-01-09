/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:08:09 by haya              #+#    #+#             */
/*   Updated: 2026/01/09 18:55:15 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int ft_atoi(char *str)
{
    int i;
    int num;

    if (!str)
        return(0);
    i = 0;
    num = 0;
    while(str[i])
    {
        num = num *10 + (str[i] - '0');
        i++;
    }
    return(num);
}

pthread_t *create_philos(int philo_num, pthread_mutex_t *forks, philo_t philo)
{
    int i;
    pthread_t *philos;
    thread_args_t *args;

    i = 0;
    philos = malloc(philo_num * sizeof(pthread_t));
    
    while(i < philo_num)
    {
        args = malloc(sizeof(thread_args_t));
        args->current_philo = i;
        args->current_philo_count = philo.philo_num;
        args->philo = philo;
        args->forks = forks;
        pthread_create(&(philos[i]), NULL, &routine, (void *)args);
        i++;
    }
    return (philos);
}

int join_philos(int philo_count, pthread_t *philos)
{
    int i;

    i = 0;
    while(i < philo_count)
    {
        if (pthread_join(philos[i],NULL) != 0)
            return (3);
        i++;
    }
    return (0);
}

void init_philo(philo_t *philo,char **argv)
{
    philo->philo_num = ft_atoi(argv[1]);
    philo->time_to_die = ft_atoi(argv[2]);
    philo->time_to_eat = ft_atoi(argv[3]);
    philo->time_to_sleep = ft_atoi(argv[4]);
    if(argv[5])
        philo->eat_count = ft_atoi(argv[5]);
    else
        philo->eat_count = 0;
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