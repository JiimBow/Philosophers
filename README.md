*This project has been created as part of the 42 curriculum by jodone*

# Philosophers

## Description

We have to write a program about the classic "Dining Philosophers" problem. Each philosopher has one fork and needs to take a fork from another philosopher sitting next to them in order to eat. Each philosopher has a time to eat, a time to sleep, and a time to die. If the time to die passes since their last meal without eating again, the philosopher dies.
Each philosopher must be represented as a separate thread, or as a separate process for the bonus part.

## Instructions

Compile, then run the program with the following arguments : 
**number_of_philosopher time_to_die time_to_eat time_to_sleep [number_of_time_each_philosopher_must_eat]**
The last argument is optional, if specified, the simulation stops when all philosophers have eaten at least **number_of_time_each_philosopher_must_eat**

## Resources
This site help me a lot to understand the principe of mutexes and threads.
https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/
Chatgpt is used for new functions which i need some explanations.
