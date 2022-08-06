/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:02:00 by root              #+#    #+#             */
/*   Updated: 2022/08/06 16:59:14 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
 *	Check les args. et init les structures.
*/

int	ft_check_arg(int ac, char **av, t_life *lf)
{
	if (ac < 5 || ac > 6)
		return (0);
	lf->num = ft_atoi(av[1]);
	if (lf->num < 1)
		return (0);
	lf->t_die = ft_atoi(av[2]);
	lf->t_eat = ft_atoi(av[3]);
	lf->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		lf->n_eat = ft_atoi(av[5]);
	else
		lf->n_eat = -1;
	lf->died = 0;
	lf->start = 0;
	pthread_mutex_init(&(lf->mem), NULL);
	pthread_mutex_init(&(lf->dis), NULL);
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
 *	ms: 10^3 sec
 *	µs:	10^6 sec
 *	sec	to ms	=> 10^3
 *	µs to ms	=> 10^-3
 */
int	get_time(void)
{
	struct timeval	ms;

	gettimeofday(&ms, NULL);
	return ((ms.tv_sec * 1000) + (ms.tv_usec / 1000));
}

void	ft_err(char *msg)
{
	printf("Error: %s\n", msg);
	exit(EXIT_FAILURE);
}
