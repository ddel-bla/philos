/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parseworld.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ddel-bla <ddel-bla@student.42madrid.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/21 08:31:02 by ddel-bla		  #+#	#+#			 */
/*   Updated: 2024/05/21 08:31:43 by ddel-bla		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

static inline bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		ft_error("Only positive numbers please.");
	if (!ft_isdigit(*str))
		ft_error("Character found. Please check input");
	while (ft_isdigit(*str))
		num = (num * 10) + *str++ - '0';
	if (num > INT_MAX)
		ft_error("INT_MAX is the max input");
	return (num);
}

static void	ft_create_philos(t_world *world)
{
	int	i;

	i = -1;
	while (++i < world->philo_num)
	{
		pthread_mutex_init(&world->forks[i].mtx_fork, NULL);
		world->forks[i].fork_id = i;
	}
}

void	ft_init_world(int ac, char **av, t_world *world)
{
	if (ac != 5 && ac != 6)
		ft_error("Please enter ./philo XXX XXX XXX [X]");
	world->philo_num = ft_atol(av[1]);
	world->philo_threads = 0;
	world->time_die = ft_atol(av[2]);
	world->time_eat = ft_atol(av[3]) * 1000;
	world->time_sleep = ft_atol(av[4]) * 1000;
	if (av[5])
		world->nbr_limit_meals = ft_atol(av[5]);
	else
		world->nbr_limit_meals = -1;
	world->end = false;
	world->all_ready = false;
	world->philos = ft_mymalloc(sizeof(t_philo) * world->philo_num);
	world->forks = ft_mymalloc(sizeof(t_fork) * world->philo_num);
	pthread_mutex_init(&world->mtx_world, NULL);
	pthread_mutex_init(&world->mtx_print, NULL);
	ft_create_philos(world);
}
