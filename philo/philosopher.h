/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:28:25 by haya              #+#    #+#             */
/*   Updated: 2026/01/11 14:13:02 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h> 
#include <sys/time.h>

typedef struct philo_s
{
    int philo_num;
    int64_t time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int eat_count;
} philo_t;

typedef struct philo_data_s
{
    philo_t *philo;
    int64_t *time_of_last_meal;
    int end_of_simulation;
    int *current_eat_count;
} philo_data_t;

typedef struct thread_args_s
{
    int current_philo;
    int64_t *current_time_last;
    int *current_eat_count;
    int *end_of_simulation;
    int current_philo_count;
    pthread_mutex_t *forks;
    philo_t *philo;
} thread_args_t;

pthread_t *create_philos(int philo_num, pthread_mutex_t *forks, philo_t *philo, philo_data_t *philo_data);
int join_philos(int philo_count, pthread_t *philos);
philo_t *init_philo(char **argv);
pthread_mutex_t *init_forks(int philo_num);
void *routine(void *args);
int64_t calc_time_now();
int create_monitor(pthread_t *monitor,philo_data_t *philo_data);
int ft_atoi(char *str);
void free_all(philo_t *philo, pthread_t *philos, philo_data_t *philo_data);
philo_data_t *init_philo_data(philo_t *philo);
void *ft_calloc(int count, unsigned long size);

#endif