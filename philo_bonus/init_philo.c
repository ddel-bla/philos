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

static void ft_eat(t_philo *philo)
{
	if (sem_wait(philo->world->s_fork) == -1)
		ft_error("sem_wait s_fork failed");
	ft_write_log(FIRST_FORK, philo);
	ft_write_log(SECOND_FORK, philo);
	philo->last_meal = ft_gettime(MILI);
	philo->meals++;
	ft_write_log(EATING, philo);
	//REVISAR FULL DECREMENTANDO MEALS 
	if (philo->world->nbr_limit_meals == philo->meals)
		philo->full = true;
	ft_myusleep(philo->world->time_eat, philo->world);
	if (sem_post(philo->world->s_fork) == -1)
		ft_error("sem_post s_fork failed");
}

static void ft_sleep(t_philo *philo)
{
	ft_write_log(SLEEPING, philo);
	ft_myusleep(philo->world->time_sleep, philo->world);
}


static void ft_thinking(t_philo *philo)
{
	long 	sleep;
	long 	eat;
	long 	think;
	long	philo_num;
	
	ft_write_log(THINKING, philo);
	philo_num = philo->world->philo_num;
	if (philo_num % 2 == 0)
		return ;
	sleep = philo->world->time_sleep;
	eat = philo->world->time_eat;
	think = eat * 1.75 - sleep;
	if (think < 0)
		return ;
	ft_myusleep(think, philo->world);
}

static void	ft_init_dinner(t_philo *philo)
{
	while (!ft_check(philo))
	{
		ft_eat(philo);
		//REVISAR FULL DECREMENTANDO MEALS
		if (philo->full || ft_check(philo))
 			break ;
		if (ft_check(philo))
			break ;
		ft_sleep(philo);
		if (ft_check(philo))
			break ;
		ft_thinking(philo);
	}
}


void ft_init_philo(t_world *world, int i)
{
	t_philo		*philo;

	philo = world->philos + i;
	philo->pid = ft_myfork();
	if (philo->pid == 0)
	{
		printf("----3\n");
		philo->id = i + 1;
		philo->full = false;
		philo->meals = 0;
		philo->world = world;
		if (sem_wait(philo->world->s_ready) == -1)
			ft_error("sem_wait s_ready failed");
		philo->last_meal = ft_gettime(MILI);
		ft_init_dinner(philo);
		exit(0);
	}
}
