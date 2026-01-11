/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:10:00 by haya              #+#    #+#             */
/*   Updated: 2026/01/11 15:07:51 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void take_left_right(thread_args_t *c_args)
{
    pthread_mutex_lock(&(c_args->forks[c_args->current_philo]));
    if(c_args->current_philo == c_args->philo->philo_num - 1)
            pthread_mutex_lock(&(c_args->forks[0]));
    else
            pthread_mutex_lock(&(c_args->forks[c_args->current_philo + 1]));
}

static void take_right_left(thread_args_t *c_args)
{
    if(c_args->current_philo == c_args->philo->philo_num - 1)
        pthread_mutex_lock(&(c_args->forks[0]));
    else
        pthread_mutex_lock(&(c_args->forks[c_args->current_philo + 1]));
    pthread_mutex_lock(&(c_args->forks[c_args->current_philo]));
}

static void return_forks(thread_args_t *c_args)
{
    if(c_args->current_philo == c_args->philo->philo_num - 1)
        pthread_mutex_unlock(&(c_args->forks[0]));
    else
        pthread_mutex_unlock(&(c_args->forks[c_args->current_philo + 1]));
    pthread_mutex_unlock(&(c_args->forks[c_args->current_philo]));
}

static void eat(thread_args_t *c_args)
{
    if(c_args->current_philo % 2 == 0)
        take_left_right(c_args);
    else
        take_right_left(c_args);
    if(*(c_args->end_of_simulation) == 1)
    {
        return_forks(c_args);
        return ;
    }
    printf("%lu philosopher:%i is eating\n", calc_time_now(), c_args->current_philo + 1);
    *(c_args->current_time_last) = calc_time_now();
    *(c_args->current_eat_count) += 1;
    usleep(c_args->philo->time_to_eat * 1000);    
    return_forks(c_args);
}

void *routine(void *args)
{
    thread_args_t *c_args;
    
    c_args = (thread_args_t *) args;
    while(*(c_args->end_of_simulation) == 0)
    {
        printf("%lu philosopher:%i is thinking\n", calc_time_now(), c_args->current_philo + 1);
        eat(c_args);
        if (*(c_args->end_of_simulation) == 1)
            break;
        printf("%lu philosopher:%i is sleeping\n", calc_time_now(), c_args->current_philo + 1);
        usleep(c_args->philo->time_to_sleep * 1000);         
    }
    free(args);
    return(NULL);
}
