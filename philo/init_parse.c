/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   init_parse.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ddel-bla <ddel-bla@student.42madrid.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/20 09:08:39 by ddel-bla		  #+#	#+#			 */
/*   Updated: 2024/05/20 09:13:51 by ddel-bla		 ###   ########.fr	   */
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
	{
		printf("Only positive numbers please.\n");
		return (-1);
	}
	if (!ft_isdigit(*str))
	{
		printf("Character found. Please check input\n");
		return (-1);
	}
	while (ft_isdigit(*str))
		num = (num * 10) + *str++ - '0';
	if (num > INT_MAX)
	{
		printf("CINT_MAX is the max input\n");
		return (-1);
	}
	return (num);
}

int	ft_parse(int ac, char **av, long p[5])
{
	if (ac != 5 && ac != 6)
		return (1);
	if (ft_atol(av[1]) == -1 || ft_atol(av[2]) == -1)
		return (1);
	p[0] = ft_atol(av[1]);
	p[1] = ft_atol(av[2]);
	if (ft_atol(av[3]) == -1 || ft_atol(av[4]) == -1)
		return (1);
	p[2] = ft_atol(av[3]) * 1000;
	p[3] = ft_atol(av[4]) * 1000;
	if (av[5])
	{
		p[4] = ft_atol(av[5]);
		if (p[4] <= 0)
		{
			printf("Check number of meals please.\n");
			return (1);
		}
	}
	else
		p[4] = -1;
	return (0);
}
