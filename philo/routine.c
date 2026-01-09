/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:10:00 by haya              #+#    #+#             */
/*   Updated: 2026/01/09 19:15:29 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void take_left_right(thread_args_t *c_args)
{
    pthread_mutex_lock(&(c_args->forks[c_args->current_philo]));
    if(c_args->current_philo == c_args->philo.philo_num - 1)
            pthread_mutex_lock(&(c_args->forks[0]));
    else
            pthread_mutex_lock(&(c_args->forks[c_args->current_philo + 1]));
}

static void take_right_left(thread_args_t *c_args)
{
    if(c_args->current_philo == c_args->philo.philo_num - 1)
        pthread_mutex_lock(&(c_args->forks[0]));
    else
        pthread_mutex_lock(&(c_args->forks[c_args->current_philo + 1]));
    pthread_mutex_lock(&(c_args->forks[c_args->current_philo]));
}

static void return_forks(thread_args_t *c_args)
{
    if(c_args->current_philo == c_args->philo.philo_num - 1)
        pthread_mutex_unlock(&(c_args->forks[0]));
    else
        pthread_mutex_unlock(&(c_args->forks[c_args->current_philo + 1]));
    pthread_mutex_unlock(&(c_args->forks[c_args->current_philo]));
    usleep(c_args->philo.time_to_sleep);
}

static void eat(thread_args_t *c_args)
{
    if(c_args->current_philo % 2 == 0)
        take_left_right(c_args);
    else
        take_right_left(c_args);
    printf("philosopher:%i has graped 2 forks\n", c_args->current_philo);
    usleep(c_args->philo.time_to_sleep * 1000);
    return_forks(c_args);
}

void *routine(void *args)
{
    thread_args_t *c_args;
    
    c_args = (thread_args_t *) args;
    // while(c_args->current_philo_count == c_args->philo.philo_num)
    // {
        eat(c_args);
        usleep(c_args->philo.time_to_sleep);
        //think ??         
    // }
    free(args);
    return(NULL);
}
