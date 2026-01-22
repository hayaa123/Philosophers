/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:10:00 by haya              #+#    #+#             */
/*   Updated: 2026/01/22 15:04:44 by haya             ###   ########.fr       */
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

// static void take_forks(thread_args_t *c_args)
// {
//     if (c_args->current_philo == c_args->philo->philo_num - 1)
//     {
//         pthread_mutex_lock(&(c_args->forks[0]));
//         pthread_mutex_lock(&(c_args->forks[c_args->current_philo]));
//     }
//     else
//     {
//         pthread_mutex_lock(&(c_args->forks[c_args->current_philo]));
//         pthread_mutex_lock(&(c_args->forks[c_args->current_philo + 1]));
//     }
// }

static void return_forks(thread_args_t *c_args)
{
    if (c_args->current_philo == c_args->philo->philo_num - 1)
        pthread_mutex_unlock(&(c_args->forks[0]));
    else
        pthread_mutex_unlock(&(c_args->forks[c_args->current_philo + 1]));
    pthread_mutex_unlock(&(c_args->forks[c_args->current_philo]));
}

void custom_usleep(int64_t micro_sec, thread_args_t *c_args)
{
    int64_t start_time;

    start_time = calc_time_now();
    while ((calc_time_now() - start_time) * 1000 < micro_sec)
    {
        if (is_end_of_simulation(c_args) == 1)
            break;
        usleep(500);
    }
}

void custom_print(thread_args_t *c_args, char *state)
{
    pthread_mutex_lock(c_args->print_mutex);
    if (is_end_of_simulation(c_args) == 1)
    {
        pthread_mutex_unlock(c_args->print_mutex);
        return;
    }
    printf("%lu %i is %s\n",
           calc_time_now() - c_args->start_of_simulation, c_args->current_philo + 1, state);
    pthread_mutex_unlock(c_args->print_mutex);
}

static void eat(thread_args_t *c_args)
{
    if ((c_args->current_philo + 1) % 2 == 0)
        take_left_right(c_args);
    else
        take_right_left(c_args);
    if (is_end_of_simulation(c_args) == 1)
    {
        return_forks(c_args);
        return;
    }
    pthread_mutex_lock(c_args->time_mutex);
    *(c_args->current_time_last) = calc_time_now();
    *(c_args->current_eat_count) += 1;
    pthread_mutex_unlock(c_args->time_mutex);
    custom_print(c_args, "eating");
    custom_usleep(c_args->philo->time_to_eat * 1000, c_args);
    return_forks(c_args);
}

void *routine(void *args)
{
    thread_args_t *c_args;

    c_args = (thread_args_t *)args;
    if ((c_args->current_philo + 1) % 2 == 0)
    {
        usleep(100);
    }
    pthread_mutex_lock(c_args->time_mutex);
    *(c_args->current_time_last) = calc_time_now();
    pthread_mutex_unlock(c_args->time_mutex);
    while (1)
    {
        if (c_args->philo->philo_num == 1)
            break;
        if (is_end_of_simulation(c_args) == 1)
            break;
        eat(c_args);
        if (is_end_of_simulation(c_args) == 1)
            break;
        custom_print(c_args, "sleeping");
        custom_usleep(c_args->philo->time_to_sleep * 1000, c_args);
        custom_print(c_args, "thinking");
        custom_usleep(10000, c_args);
    }
    free(args);
    return (NULL);
}
