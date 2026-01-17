/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:10:00 by haya              #+#    #+#             */
/*   Updated: 2026/01/17 17:10:13 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void take_left_right(thread_args_t *c_args)
{
    pthread_mutex_lock(&(c_args->forks[c_args->current_philo]));
    if (c_args->current_philo == c_args->philo->philo_num - 1)
        pthread_mutex_lock(&(c_args->forks[0]));
    else
        pthread_mutex_lock(&(c_args->forks[c_args->current_philo + 1]));
}

static void take_right_left(thread_args_t *c_args)
{
    if (c_args->current_philo == c_args->philo->philo_num - 1)
        pthread_mutex_lock(&(c_args->forks[0]));
    else
        pthread_mutex_lock(&(c_args->forks[c_args->current_philo + 1]));
    pthread_mutex_lock(&(c_args->forks[c_args->current_philo]));
}

static void return_forks(thread_args_t *c_args)
{
    if (c_args->current_philo == c_args->philo->philo_num - 1)
        pthread_mutex_unlock(&(c_args->forks[0]));
    else
        pthread_mutex_unlock(&(c_args->forks[c_args->current_philo + 1]));
    pthread_mutex_unlock(&(c_args->forks[c_args->current_philo]));
}

static void eat(thread_args_t *c_args)
{
    if (c_args->current_philo % 2 == 0)
        take_left_right(c_args);
    else
        take_right_left(c_args);
    pthread_mutex_lock(c_args->time_mutex);
    *(c_args->current_time_last) = calc_time_now();
    *(c_args->current_eat_count) += 1;
    pthread_mutex_unlock(c_args->time_mutex);
    pthread_mutex_lock(c_args->end_mutext);
    if (*(c_args->end_of_simulation) == 1)
    {
        pthread_mutex_unlock(c_args->end_mutext);
        return_forks(c_args);
        return;
    }
    pthread_mutex_unlock(c_args->end_mutext);
    pthread_mutex_lock(c_args->print_mutex);
    printf("%lu philosopher:%i is eating\n",
           calc_time_now() - c_args->start_of_simulation, c_args->current_philo + 1);
    pthread_mutex_unlock(c_args->print_mutex);
    usleep(c_args->philo->time_to_eat * 1000);
    return_forks(c_args);
}

void *routine(void *args)
{
    thread_args_t *c_args;

    c_args = (thread_args_t *)args;
    while (1)
    {
        if (c_args->philo->philo_num == 1)
            break;
        pthread_mutex_lock(c_args->end_mutext);
        if (*(c_args->end_of_simulation) == 1)
        {
            pthread_mutex_unlock(c_args->end_mutext);
            break;
        }
        else
            pthread_mutex_lock(c_args->print_mutex);
        printf("%lu philosopher:%i is thinking\n", calc_time_now() - c_args->start_of_simulation, c_args->current_philo + 1);
        pthread_mutex_unlock(c_args->print_mutex);
        pthread_mutex_unlock(c_args->end_mutext);
        eat(c_args);
        pthread_mutex_lock(c_args->end_mutext);
        if (*(c_args->end_of_simulation) == 1)
        {
            pthread_mutex_unlock(c_args->end_mutext);
            break;
        }

        pthread_mutex_unlock(c_args->end_mutext);
        pthread_mutex_lock(c_args->print_mutex);
        printf("%lu philosopher:%i is sleeping\n", calc_time_now() - c_args->start_of_simulation, c_args->current_philo + 1);
        pthread_mutex_unlock(c_args->print_mutex);
        usleep(c_args->philo->time_to_sleep * 1000);
    }
    free(args);
    return (NULL);
}
