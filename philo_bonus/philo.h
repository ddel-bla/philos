/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   philo.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ddel-bla <ddel-bla@student.42madrid.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/20 08:31:42 by ddel-bla		  #+#	#+#			 */
/*   Updated: 2024/05/20 08:31:42 by ddel-bla		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdint.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include <errno.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

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
	FIRST_FORK,
	SECOND_FORK,
	DIED,
}			t_life;

typedef struct s_world	t_world;
typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;

struct s_philo
{
	long		meals;
	long		last_meal;
	int			id;
	int			pid;
	bool		full;
	t_world		*world;
};

struct	s_world	
{
	long		philo_num;
	long		philo_threads;
	long		time_die;
	long		time_eat;
	long		time_sleep;
	long		nbr_limit_meals;
	long		start;
	int			scan_pid;
	bool		end;
	t_philo		*philos;
	sem_t		*s_fork;
	sem_t		*s_ready;
	sem_t		*s_end;
	sem_t		*s_write;
};

void	ft_init_philo(t_world *world, int i);

int		ft_init_world(int ac, char **av, t_world *world);

long	ft_gettime(t_time timecode);
void	ft_myusleep(long usec, t_world *world);
bool	ft_finished(t_world *world);
bool	ft_philo_died(t_philo *philo);
bool	ft_check(t_philo *philo);

void	ft_error(const char *error);
void	*ft_mymalloc(size_t bytes);
int		ft_myfork(void);
void	ft_write_log(t_life status, t_philo *philo);

#endif