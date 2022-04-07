/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:02:00 by root              #+#    #+#             */
/*   Updated: 2022/04/07 17:23:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_check_arg(int ac, char **av, t_life *ph)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (0);
	ph->num = ft_atoi(av[1]);
	ph->t_die = ft_atoi(av[2]);
	ph->t_eat = ft_atoi(av[3]);
	ph->t_sleep = ft_atoi(av[4]);
	if (ac > 5)
		ph->plan = ft_atoi(av[5]);
	else
		ph->plan = 0;
	return (1);
}

/*
 *	tv_sec	->	seconds	
 *	tv_usec	->	microseconds
 *	le nombre de secondes et microsecondes
 *		écoulées depuis le 1er janvier 1970.
 *	------------------------
 *	Convertit les 2 donnees pour avoir un temps
 *		en millisecondes.
 *	1 sec -> 10^-3 ms	=> * 1000
 *	1 sec -> 10^-6 µs	=> / 1000
 */
int	ft_gettime(void)
{
	struct timeval	ms;

	gettimeofday(&ms, NULL);
	printf("time: %ld ms\n", (ms.tv_sec * 1000) + (ms.tv_usec / 1000));
	return (1);
}