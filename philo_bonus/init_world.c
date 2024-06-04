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

int	ft_init_world(int ac, char **av, t_world *w)
{
	if (ac != 5 && ac != 6)
		return (1);
	w->philo_num = ft_atol(av[1]);
	w->time_die = ft_atol(av[2]);
	w->time_eat = ft_atol(av[3]) * 1000;
	w->time_sleep = ft_atol(av[4]) * 1000;
	if (av[5])
		w->nbr_limit_meals = ft_atol(av[5]);
	else
		w->nbr_limit_meals = -1;
	w->end = false;
	w->philos = ft_mymalloc(sizeof(t_philo) * w->philo_num);
	w->s_fork = ft_sem_open("/forks", w->philo_num);
	w->s_ready = ft_sem_open("/ready", 0);
	w->s_end = ft_sem_open("/end", 1);
	w->s_write = ft_sem_open("/write", 1);
	w->start = ft_gettime(MILI);
	return (0);
}
