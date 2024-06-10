/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:14:39 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/06/06 12:14:39 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <pthread.h>

typedef enum e_time
{
	MILI,
	MICRO,
}			t_time;

typedef enum e_life
{
	EATING,
	SLEEPING,
	THINKING,
	FORK,
	DIED,
}			t_life;

typedef struct s_world	t_world;
typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;

struct s_philo
{
	long		meals;
	long		last_meal;
	long		next_meal;
	long		die_time;
	int			id;
	int			pid;
	t_world		*world;
};

struct	s_world	
{
	long		philo_num;
	long		time_die;
	long		time_eat;
	long		time_sleep;
	long		nbr_limit_meals;
	long		start;
	t_philo		*philos;
	sem_t		*s_fork;
	sem_t		*s_ready;
	sem_t		*s_end;
	sem_t		*s_write;
};

void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_thinking(t_philo *philo);
void	ft_write_log(t_life status, t_philo *philo);

void	ft_init_philo(t_world *world, int i);

void	ft_init_world(char **av, t_world *world);

void	ft_exit(t_world *world);

void	ft_error(t_world *world, const char *error, int numerr);
void	*ft_mymalloc(size_t bytes);
int		ft_myfork(void);

sem_t	*ft_sem_open(char *str, long num);
void	ft_sem_wait(sem_t *sem);
void	ft_sem_post(sem_t *sem);
void	ft_sem_close(sem_t *sem);
void	ft_sem_unlink(char *sem);

void	*ft_scan_f_die(void *arg);
void	*ft_scan_f_alive(void *arg);

long	ft_atol(const char *str);
char	*ft_itoa(long n);

long	ft_gettime(t_time timecode);
void	ft_myusleep(long usec);
void	ft_delaying(t_philo *philo, int init);

#endif