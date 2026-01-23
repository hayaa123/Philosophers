*This project has been created as part of the 42 curriculum by hal-lawa*

# Description
Philosophers project is intended to make a dining philosophers simulation by implementing threads and mutexes.
Dining Philosopher problem : there are an n philosophers sitting in a round table, betwen each tow philosophers there is one forks making the fork count equals philosopher count, the round table contain a spaggitte bawl that philosophers can eat from to survive. to eat from the bawl a philosopher need two forks, the simulation stops when a philosopher dies from starvation.

In this project each philosopher is represented by a thread, the forks is represented by mutex.

# Instructions
To run this project follow these steps:
- clone this repository using `git clone <repo url>` command.
- Run `make` command in the terminal, `make debug` for debugging.
- run the project by using `./philo <number_of_philosophers> <time_to_die> <time_to_eat time_to_sleep> <[number_of_times_each_philosopher_must_eat]>`, all the arguments are mandatory expect the "number_of_times_each_philosopher_must_eat".

# Resources
- [Unix Threads in C play list by CodeVault](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
- ch 29 from the [The Linux Programming Interface]
- My peer (abdsalah)[https://github.com/Abusalah0] help in testing and debugging :D.

#