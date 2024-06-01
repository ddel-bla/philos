/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   init_threads.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ddel-bla <ddel-bla@student.42madrid.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/23 06:53:14 by ddel-bla		  #+#	#+#			 */
/*   Updated: 2024/05/23 07:13:27 by ddel-bla		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

static void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first->mtx_fork);
	ft_write_log(FIRST_FORK, philo);
	pthread_mutex_lock(&philo->second->mtx_fork);
	ft_write_log(SECOND_FORK, philo);
	ft_set_l(&philo->mtx_philo, &philo->last_meal, ft_gettime(MILI));
	ft_write_log(EATING, philo);
	philo->meals--;
	ft_myusleep(philo->world->time_eat, philo->world);
	pthread_mutex_unlock(&philo->first->mtx_fork);
	pthread_mutex_unlock(&philo->second->mtx_fork);
}

static void	ft_sleep(t_philo *philo)
{
	ft_write_log(SLEEPING, philo);
	ft_myusleep(philo->world->time_sleep, philo->world);
}

static void	ft_thinking(t_philo *philo)
{
	long	philo_num;

	ft_write_log(THINKING, philo);
	philo_num = ft_get_l(&philo->world->mtx_world, &philo->world->philo_num);
	if (philo_num % 2 == 0)
		return ;
	ft_delaying(philo, 0);
}

void	*ft_init_threads(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	ft_wait_all_threads(philo->world);
	philo->last_meal = ft_gettime(MILI);
	ft_add_l(&philo->world->mtx_world, &philo->world->philo_threads);
	if (philo->id % 2 == 0)
		ft_delaying(philo, 1);
	while (!ft_finished(philo->world))
	{
		if (!ft_get_l(&philo->mtx_philo, &philo->meals) != 0)
			break ;
		ft_eat(philo);
		ft_sleep(philo);
		ft_thinking(philo);
	}
	return (NULL);
}

void	*ft_one_thread(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	ft_set_l(&philo->mtx_philo, &philo->last_meal, ft_gettime(MILI));
	ft_wait_all_threads(philo->world);
	ft_add_l(&philo->world->mtx_world, &philo->world->philo_threads);
	ft_write_log(FIRST_FORK, philo);
	while (!ft_finished(philo->world))
		;
	return (NULL);
}
