/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:27:55 by haya              #+#    #+#             */
/*   Updated: 2026/01/11 14:50:05 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int all_eat_enough(philo_data_t *philo_data)
{
    int i;
        
    i = 0;
    while(i < philo_data->philo->philo_num)
    {
        if(philo_data->current_eat_count[i] < philo_data->philo->eat_count)
            return (0);
        i++;
    }
    philo_data->end_of_simulation = 1;
    printf("All Philosopher has eat enough times :D\n");
    return (1);
}

static void *monitor_routine(void  *philo_d)
{
    philo_data_t *philo_c;
    int i;
    
    philo_c = philo_d;
    while(1)
    {
        i = 0;
        while(i < philo_c->philo->philo_num)
        {
            if(calc_time_now() - (philo_c->time_of_last_meal[i]) >= philo_c->philo->time_to_die)
            {
                printf("%lu Philosopher %i died\n", calc_time_now(), i + 1);
                philo_c->end_of_simulation = 1;
                break;      
            }
            i++;
        }
        if(philo_c->end_of_simulation)
            break;
        if(all_eat_enough(philo_c))
            break;
    } 
    return (NULL);
}

int create_monitor(pthread_t *monitor,philo_data_t *philo_data)
{
    if(pthread_create(monitor, NULL, &monitor_routine, (void *)philo_data) != 0)
        return (1);
    return (0);
}