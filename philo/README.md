*This project has been created as part of the 42 curriculum by hal-lawa*

# Description
The Philosophers project aims to simulate the Dining Philosophers problem using threads and mutexes.

In the Dining Philosophers problem, there are N philosophers sitting around a round table. Between each pair of philosophers, there is one fork, so the number of forks is equal to the number of philosophers. In the center of the table, there is a bowl of spaghetti from which the philosophers eat to survive. To eat from the bowl, a philosopher must hold two forks.
The simulation stops when a philosopher dies from starvation.

After eating, a philosopher sleeps and then starts thinking again.

In this project, each philosopher is represented by a thread, and each fork is represented by a mutex.

# Instructions
To run this project, follow these steps:
- Clone this repository using `git clone <repo url>` command.
- Run `make` command in the terminal (`make debug` for debugging).
- Run the program using:

```
./philo <number_of_philosophers> <time_to_die> <time_to_eat time_to_sleep> <[number_of_times_each_philosopher_must_eat]>
```
- For example
```
./philo 5 800 200 200 10
```
all the arguments are mandatory expect the `number_of_times_each_philosopher_must_eat`.

# Resources
- [Unix Threads in C play list by CodeVault](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
- Ch 29 from the [The Linux Programming Interface]
- My peer [abdsalah](https://github.com/Abusalah0) helped with testing and debugging 😀.

### AI usage:
- I used ChatGPT to understand the monitor concept and the shared data between the monitor and the philosophers.
- I used Copilot to understand why printf can cause a data race and why it needs a mutex.
