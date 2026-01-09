#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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
    int current_philo_count;
    pthread_mutex_t *forks;
    philo_t philo;
} thread_args_t;

pthread_t *create_philos(int philo_num, pthread_mutex_t *forks, philo_t philo);
int join_philos(int philo_count, pthread_t *philos);
void init_philo(philo_t *philo,char **argv);
pthread_mutex_t *init_forks(int philo_num);
void *routine(void *args);