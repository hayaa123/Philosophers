/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:58:23 by haya              #+#    #+#             */
/*   Updated: 2026/01/21 21:43:46 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// void philo_sleep(thread_args_t *c_args)
// {
//     pthread_mutex_lock(c_args->print_mutex);
//     printf("%lu philosopher:%i is sleeping\n", calc_time_now() - c_args->start_of_simulation, c_args->current_philo + 1);
//     pthread_mutex_unlock(c_args->print_mutex);
//     custom_usleep(c_args->philo->time_to_sleep * 1000, c_args);
// }

// void philo_think(thread_args_t *c_args)
// {
//     pthread_mutex_lock(c_args->print_mutex);
//     printf("%lu philosopher:%i is thinking\n", calc_time_now() - c_args->start_of_simulation, c_args->current_philo + 1);
//     pthread_mutex_unlock(c_args->print_mutex);
// }

int is_end_of_simulation(thread_args_t *c_args)
{
    pthread_mutex_lock(c_args->end_mutext);
    if (*(c_args->end_of_simulation) == 1)
    {
        pthread_mutex_unlock(c_args->end_mutext);
        return (1);
    }
    pthread_mutex_unlock(c_args->end_mutext);
    return(0);
}