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
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdint.h>
# include <limits.h>
# include <string.h>

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

typedef pthread_mutex_t		t_mtx;
typedef struct s_world		t_world;
typedef struct s_philo		t_philo;
typedef struct s_fork		t_fork;

struct s_fork
{
	t_mtx		mtx_fork;
	int			fork_id;
};

struct s_philo
{
	long		meals;
	long		last_meal;
	int			id;
	t_fork		*first;
	t_fork		*second;
	pthread_t	thread_id;
	t_mtx		mtx_philo;
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
	bool		end;
	bool		all_ready;
	pthread_t	thread_id;
	t_mtx		mtx_world;
	t_mtx		mtx_print;
	t_fork		*forks;
	t_philo		*philos;
};

int		ft_parse(int ac, char **av, long p[5]);

void	ft_init_philos(t_world *world);

void	*ft_init_threads(void *data);
void	*ft_one_thread(void *data);

void	ft_init_world(t_world *world, long p[5]);

void	ft_set_b(t_mtx *mutex, bool *dst, bool value);
bool	ft_get_b(t_mtx *mutex, bool *value);
void	ft_set_l(t_mtx *mutex, long *dst, long value);
long	ft_get_l(t_mtx *mutex, long *value);
void	ft_add_l(t_mtx *mutex, long *value, int direction);

void	ft_wait_all_threads(t_world *world);
bool	ft_finished(t_world *world);
void	*ft_scan_world(void	*data);

long	ft_gettime(t_time timecode);
void	ft_myusleep(long usec, t_world *world);
void	ft_delaying(t_philo *philo, int init);

void	*ft_mymalloc(size_t bytes);
void	ft_write_log(t_life status, t_philo *philo);

#endif