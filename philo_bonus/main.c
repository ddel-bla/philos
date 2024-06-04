/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ddel-bla <ddel-bla@student.42madrid.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/20 08:31:34 by ddel-bla		  #+#	#+#			 */
/*   Updated: 2024/05/20 08:31:34 by ddel-bla		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

static void	ft_exit(t_world *world)
{
	if (sem_close(world->s_fork) == -1)
		ft_error ("sem_close failed");
	if (sem_unlink("/forks") == -1)
		ft_error ("sem_unlink s_fork failed");
	if (sem_close(world->s_ready) == -1)
		ft_error ("sem_close failed");
	if (sem_unlink("/ready") == -1)
		ft_error ("sem_unlink /ready failed");
	if (sem_close(world->s_end) == -1)
		ft_error ("sem_close failed");
	if (sem_unlink("/end") == -1)
		ft_error ("sem_unlink /end failed");
	if (sem_close(world->s_write) == -1)
		ft_error ("sem_close failed");
	if (sem_unlink("/write") == -1)
		ft_error ("sem_unlink /write failed");
	free(world->philos);
}

int	main(int ac, char **av)
{
	t_world		world;
	int			i;

	if (ft_init_world(ac, av, &world))
		ft_error("Please enter ./philo XXX XXX XXX [X]");
	if (world.nbr_limit_meals == 0)
		ft_error("Check number of meals please.");
	i = -1;
	while (++i < world.philo_num)
	{
//		printf("Xa %i\n", i);
		ft_init_philo(&world, i);
	}
	while (--i > -1)
	{
//		printf("Xb %i\n", i);
		if (sem_post(world.s_ready) == -1)
			ft_error("sem_post failed");
	}
	ft_scan_world(&world);
	while (++i < world.philo_num)
		waitpid(world.philos[i].pid, NULL, 0);
	ft_exit(&world);
	return (0);
}
