*This project has been created as part of the 42 curriculum by jodone*

# Philosophers

## Description

We have to write a program about the iconic problem of Philosophers. Each philosophers had one fork, and need to take a fork from another philosophers, who's next to them, to eat. Each philosophers had a time to eat, a time to sleep, and a time to die, which if this time pass from their last meal, without eating again, kill them.
Each philosopher must be represented as a separate thread.

## Instructions

Make, then run the program with the following arguments : 
**number_of_philosopher time_to_die time_to_eat time_to_sleep [number_of_time_each_philosopher_must_eat]**
The last argument is optional, but if specified, the simulation stop when all philosophers have eaten at least **number_of_time_each_philosopher_must_eat**

## Resources
This site help me a lot to understand the principe of mutex and thread.
https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/
Chatgpt is used for new functions which i need some explanations.
