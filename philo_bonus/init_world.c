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
	printf("----1\n");
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
	w->s_fork = sem_open("/forks", O_CREAT, 0644, (int) w->philo_num / 2);
	w->s_ready = sem_open("/ready", O_CREAT, 0644, 0);
	w->s_end = sem_open("/end", O_CREAT, 0644, 1);
	w->s_write = sem_open("/write", O_CREAT, 0644, 1);
	w->start = ft_gettime(MILI);
	printf("----2\n");
	return (0);
}
