/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ddel-bla <ddel-bla@student.42madrid.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/20 08:31:46 by ddel-bla		  #+#	#+#			 */
/*   Updated: 2024/05/20 08:31:46 by ddel-bla		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

void	*ft_mymalloc(size_t bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (!ptr)
		return (NULL);
	return (ptr);
}

void	ft_write_log(t_life status, t_philo *philo)
{
	long	elapsed;

	elapsed = ft_gettime(MILI) - philo->world->start;
	if (!ft_get_l(&philo->mtx_philo, &philo->meals))
		return ;
	pthread_mutex_lock(&philo->world->mtx_print);
	if ((FIRST_FORK == status || SECOND_FORK == status)
		&& !ft_finished(philo->world))
		printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
	else if (EATING == status && !ft_finished(philo->world))
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (SLEEPING == status && !ft_finished(philo->world))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !ft_finished(philo->world))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf("%-6ld %d died\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->world->mtx_print);
}
