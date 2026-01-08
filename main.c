#include "philosopher.h"

int ft_atoi(char *str)
{
    int i;
    int num;

    if (!str)
        return(0);
    i = 0;
    num = 0;
    while(str[i])
    {
        num = num *10 + (str[i] - '0');
        i++;
    }
    return(num);
}

void init_philo(philo_t *philo,char **argv)
{
    philo->philo_num = ft_atoi(argv[1]);
    philo->time_to_die = ft_atoi(argv[2]);
    philo->time_to_eat = ft_atoi(argv[3]);
    philo->time_to_sleep = ft_atoi(argv[4]);
    if(argv[5])
        philo->eat_count = ft_atoi(argv[5]);
    else
        philo->eat_count = 0;
}

pthread_mutex_t *init_forks(int philo_num)
{
    pthread_mutex_t *forks;
    int i;

    forks = malloc(philo_num * sizeof(pthread_mutex_t));
    i = 0;
    if(!forks)
        return (NULL);
    while(i < philo_num)
    {
        pthread_mutex_init(&(forks[i]), NULL);
        i++;
    }
    return (forks);
}

void destroy_forks(int philo_num, pthread_mutex_t *forks)
{
    int i;

    i = 0;
    while(i < philo_num)
    {
        pthread_mutex_destroy(&(forks[i]));
        i++;
    }
    free(forks);
}

void *routine(void *args)
{
    thread_args_t *casted_args;
    
    casted_args = (thread_args_t *) args;
    // printf("current_philo: %i\n", casted_args->current_philo);
    if(casted_args->current_philo == casted_args->philo.philo_num - 1)
            pthread_mutex_lock(&(casted_args->forks[0]));
    else
            pthread_mutex_lock(&(casted_args->forks[casted_args->current_philo + 1]));
    pthread_mutex_lock(&(casted_args->forks[casted_args->current_philo]));

    printf("philosopher:%i has graped 2 forks\n", casted_args->current_philo);
    sleep(1);

    if(casted_args->current_philo == casted_args->philo.philo_num - 1)
            pthread_mutex_unlock(&(casted_args->forks[0]));
    else
            pthread_mutex_unlock(&(casted_args->forks[casted_args->current_philo + 1]));
    pthread_mutex_unlock(&(casted_args->forks[casted_args->current_philo]));
    return(NULL);
}

pthread_t *create_philos(int philo_num, pthread_mutex_t *forks, philo_t philo)
{
    int i;
    pthread_t *philos;
    thread_args_t *args;

    i = 0;
    philos = malloc(philo_num * sizeof(pthread_t));
    while(i < philo_num)
    {
        args = malloc(sizeof(thread_args_t));
        args->current_philo = i;
        args->philo = philo;
        args->forks = forks;
        pthread_create(&(philos[i]), NULL, &routine, (void *)args);
        i++;
    }
    return (philos);
}

int join_philos(int philo_count, pthread_t *philos)
{
    int i;

    i = 0;
    while(i < philo_count)
    {
        if (pthread_join(philos[i],NULL) != 0)
            return (3);
        i++;
    }
    return (0);
}

int main(int argc, char **argv)
{
    philo_t philo;
    pthread_t *philos;
    pthread_mutex_t *forks;

    if(argc < 1 || argc > 6)
        return(1);
    
    init_philo(&philo, argv);
    forks = init_forks(philo.philo_num);
    philos = create_philos(philo.philo_num, forks, philo);
    if(join_philos(philo.philo_num, philos) != 0 )
        return (3);
    free(philos);
    destroy_forks(philo.philo_num, forks);
}
