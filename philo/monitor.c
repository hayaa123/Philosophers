/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:27:55 by haya              #+#    #+#             */
/*   Updated: 2026/01/13 12:27:28 by haya             ###   ########.fr       */
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

int check_death(philo_data_t *philo_c)
{
    int i;
    int64_t now;
    
    i = 0;
    while(i < philo_c->philo->philo_num)
    {
        pthread_mutex_lock(&(philo_c->time_mutex[i]));
        now = calc_time_now();
        if(now == 0)
            return (0);
        if(now - (philo_c->time_of_last_meal[i]) >= philo_c->philo->time_to_die)
        {
            pthread_mutex_lock(philo_c->end_mutex);
            philo_c->end_of_simulation = 1;
            pthread_mutex_unlock(philo_c->end_mutex);
            printf("%lu Philosopher %i died\n",
                philo_c->time_of_last_meal[i] + philo_c->philo-> time_to_die,
                 i + 1);
            pthread_mutex_unlock(&(philo_c->time_mutex[i]));
            break;      
        }
        pthread_mutex_unlock(&(philo_c->time_mutex[i]));
        i++;
    }
    return (1);
}


static void *monitor_routine(void  *philo_d)
{
    philo_data_t *philo_c;
    
    philo_c = philo_d;
    while(1)
    {
        if(check_death(philo_c) == 0)
        {
            pthread_mutex_lock(philo_c->end_mutex);
            philo_c->end_of_simulation = 1;
            pthread_mutex_unlock(philo_c->end_mutex);
            return (NULL);
        }
        pthread_mutex_lock(philo_c->end_mutex);
        if(philo_c->end_of_simulation)
        {
            pthread_mutex_unlock(philo_c->end_mutex);
            break;
        }
        if(philo_c->philo->eat_count != 0 && all_eat_enough(philo_c))
        {
            pthread_mutex_unlock(philo_c->end_mutex);
            break;
        }
        pthread_mutex_unlock(philo_c->end_mutex);
        usleep(1000);
    } 
    return (NULL);
}

int create_monitor(pthread_t *monitor,philo_data_t *philo_data)
{
    if(pthread_create(monitor, NULL, &monitor_routine, (void *)philo_data) != 0)
        return (1);
    return (0);
}