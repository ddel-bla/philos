/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   init.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ddel-bla <ddel-bla@student.42madrid.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/20 09:08:39 by ddel-bla		  #+#	#+#			 */
/*   Updated: 2024/05/20 09:13:51 by ddel-bla		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

static void	ft_eat(t_philo *philo)
{
	printf("1 pid %i\n", philo->pid);
	if (sem_wait(philo->world->s_fork) == -1)
		ft_error("sem_wait s_fork failed");
	ft_write_log(FIRST_FORK, philo);
	printf("2 pid %i\n", philo->pid);
	if (sem_wait(philo->world->s_fork) == -1)
		ft_error("sem_wait s_fork failed");
	ft_write_log(SECOND_FORK, philo);
	philo->last_meal = ft_gettime(MILI);
	ft_write_log(EATING, philo);
	philo->meals--;
	ft_myusleep(philo->world->time_eat, philo->world);
	if (sem_post(philo->world->s_fork) == -1)
		ft_error("sem_post s_fork failed");
	if (sem_post(philo->world->s_fork) == -1)
		ft_error("sem_post s_fork failed");
}

static void	ft_sleep(t_philo *philo)
{
	ft_write_log(SLEEPING, philo);
	ft_myusleep(philo->world->time_sleep, philo->world);
}

static void	ft_thinking(t_philo *philo)
{
	ft_write_log(THINKING, philo);
	if (philo->world->philo_num % 2 == 0)
		return ;
	ft_delaying(philo, 0);
}

static void	ft_init_dinner(t_philo *philo)
{
	while (!ft_check(philo))
	{
		ft_eat(philo);
		if (philo->meals == 0 || ft_check(philo))
		{
			printf("Z pid %i\n", philo->pid);
			break ;
		}
		if (ft_check(philo))
		{
			printf("X pid %i\n", philo->pid);
			break ;
		}
		ft_sleep(philo);
		if (ft_check(philo))
		{
			printf("C pid %i\n", philo->pid);
			break ;
		}
		ft_thinking(philo);
	}
}

void	ft_init_philo(t_world *world, int i)
{
	t_philo		*philo;

	philo = world->philos + i;
	philo->pid = ft_myfork();
	if (philo->pid == 0)
	{
		if (sem_wait(philo->world->s_ready) == -1)
			ft_error("sem_wait s_ready failed");
		if (philo->id % 2 == 0)
			ft_delaying(philo, 1);
		philo->id = i + 1;
		philo->meals = world->nbr_limit_meals;
		philo->world = world;
		philo->last_meal = ft_gettime(MILI);
		ft_init_dinner(philo);
		printf("4 pid %i\n", philo->pid);
		exit(0);
	}
}
