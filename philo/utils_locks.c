/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   locks_utils.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ddel-bla <ddel-bla@student.42madrid.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/20 22:05:45 by ddel-bla		  #+#	#+#			 */
/*   Updated: 2024/05/21 08:37:28 by ddel-bla		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

void	ft_set_b(t_mtx *mutex, bool *dst, bool value)
{
	pthread_mutex_lock(mutex);
	*dst = value;
	pthread_mutex_unlock(mutex);
}

bool	ft_get_b(t_mtx *mutex, bool *value)
{
	bool	ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	ft_set_l(t_mtx *mutex, long *dst, long value)
{
	pthread_mutex_lock(mutex);
	*dst = value;
	pthread_mutex_unlock(mutex);
}

long	ft_get_l(t_mtx *mutex, long *value)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	ft_add_l(t_mtx *mutex, long *value, int direction)
{
	pthread_mutex_lock(mutex);
	if (direction)
		(*value)++;
	else
		(*value)--;
	pthread_mutex_unlock(mutex);
}
