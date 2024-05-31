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

static inline bool ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static long ft_atol(const char *str)
{
	long	 num;

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

int		ft_init_world(int ac, char **av, t_world *world)
{
	//printf("----1\n");	
	if (ac != 5 && ac != 6)
		return (1);
	world->philo_num = ft_atol(av[1]);
	world->time_die = ft_atol(av[2]);
	world->time_eat = ft_atol(av[3]) * 1000;
	world->time_sleep = ft_atol(av[4]) * 1000;
	if (av[5])
		world->nbr_limit_meals = ft_atol(av[5]);
	else
		world->nbr_limit_meals = -1;
	world->end = false;
	world->philos = ft_mymalloc(sizeof(t_philo) * world->philo_num);
	world->s_fork = sem_open("/forks", O_CREAT, 0644, (int) world->philo_num / 2);
	world->s_ready = sem_open("/ready", O_CREAT, 0644, 0);
	world->s_end = sem_open("/end", O_CREAT, 0644, 1);
	world->s_write = sem_open("/write", O_CREAT, 0644, 1);
	world->start = ft_gettime(MILI);
	//printf("----2\n");
	return (0);

}
