<p align="center">
  <a>
    <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/8d/42_Logo.svg/1200px-42_Logo.svg.png" alt="Logo" width="200" height="200">
  </a>

  <p align="center">
    I never thought philosophy would be so deadly<br>
    Project philosophers of 42 school
    <br />
	</p>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Makefile-8A2BE2">
  <img src="https://img.shields.io/badge/C-4682B4">
  <img src="https://img.shields.io/badge/Shell-2E8B57">
  <img src="https://img.shields.io/badge/Gcc-00FF00">
  
</p>

## &#x1F4CC; Index 
- [What is philosophers?](#-what-is-philosophers)
- [Rules](#-rules)
- [Set the params](#-set-the-params)
- [Usage](#-usage)
- [Examples](#-examples)

## &#x2728; What is philosophers?

This project is a training to multi-threads/multi-process programming with the use of mutex and semaphore.
It contains N different proccess or threads simulating the famous Dining Philosophers problem, all with the same basic rules.
Optimization is a must to ensure the survival of our philosophers.

<p align="center">
  <img width="231" alt="Screen Shot 2024-03-07 at 1 41 44 PM" src="https://github.com/vcereced/philosopher/assets/120835200/7a70dcc9-6f4a-4286-95dc-51155e994e4b">
</p>

## 🕹 Rules

| | |
|---|---|
|&#x1F480;| The philosophers must never be starving, they need to eat.|
|&#x274C;| The simulation stops when a philosopher dies.|
|&#x23F3;| No more than 10 ms between the death and print its death.|
|&#x1F5A8;| The status printed should not be messed with another philosopher’s status.|
|&#127869;| While `eating`, they are not `thinking` or `sleeping`. |
|&#x1F634;| While `sleeping`, they are not `eating` or `thinking`.|
|&#x1F914;| While `thinking`, they are not `eating` or `sleeping`.|
|&#x1F374; &#x1F374;| Philosopher must eat with two forks, one for each hand. |
|&#x1F4AC;| Philosophers don’t speak with each other. |
|&#x1F4AD;| Philosophers don’t know when another philosopher is about to die. |
|&#127869;&#x2192;&#x1F374;&#x1F374;&#x2192;&#x1F634;  | Each time a philosopher has finished `eating`, he will drop his forks and start `sleeping`. |
|&#x1F634;&#x2192;&#x1F914; | When a philosopher is done `sleeping`, he will start `thinking`. |
|&#x1F914;&#x2192;&#x1F374;&#x1F374;&#x2192;&#127869;  | When a philosopher is done `thinking`, he will take 2 forks to `eating`. |

## 🛠 Set the params

| | |
|---|---|
|`number_of_philosophers`| number of philosophers (process / threads). |
|`time_to_die`| Miliseconds after starting his last `eating` or start de simulation to die. |
|`time_to_eat`| Milliseconds will spend to `eating` after take the 2 forks. |
|`time_to_sleep`| Milliseconds will spend to `sleeping`. |
|`number_of_times_each_philosopher_must_eat`| [optional]. If all ate at least `number_of_times_each_philosopher_must_eat`, simulation finish. If not specified, simulation continue till someone die.|
|`number_of_philosophers`| number of philosophers (process / threads). |


## &#x1F4BB; Usage

`cd philo && make` to compile the executable with threads / mutex.

`cd philo_bonus && make` to compile the executable with process / semaphores.

`make clean` remove .o files.

`make fclean` remove .o files and .a files and executable.

## &#x1F4D6; Examples

The arguments of the executable should be:
```bash
number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Execute whith the arguments in the terminal.

```bash
./philo 4 310 200 100
```

Should one philosopher die. Output should be:

<img width="377" alt="Screen Shot 2024-03-07 at 5 37 21 PM" src="https://github.com/vcereced/philosopher/assets/120835200/c7a4e095-354e-4788-a005-05f01977d02d">

Execute the bonus whith the arguments in the terminal.

```bash
./philo_bonus 4 410 200 100 1
```
 Output should be:

 <img width="377" alt="Screen Shot 2024-03-07 at 5 42 35 PM" src="https://github.com/vcereced/philosopher/assets/120835200/a22b1c3d-adcd-4d59-a1c1-faf567a40e12">




