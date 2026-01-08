#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct philo_s
{
    int philo_num;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int eat_count;
} philo_t;

typedef struct thread_args_s
{
    int current_philo;
    pthread_mutex_t *forks;
    philo_t philo;
} thread_args_t;