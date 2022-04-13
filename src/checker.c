/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:02:00 by root              #+#    #+#             */
/*   Updated: 2022/04/13 22:01:56 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
 *	Check les args. et init les structures.
*/

int	ft_check_arg(int ac, char **av, t_life *lf)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (0);
	lf->num = ft_atoi(av[1]);
	lf->t_die = ft_atoi(av[2]);
	lf->t_eat = ft_atoi(av[3]);
	lf->t_sleep = ft_atoi(av[4]);
	if (ac > 5)
		lf->n_eat = ft_atoi(av[5]);
	else
		lf->n_eat = 0;
	lf->philos = (t_philo *)malloc(sizeof(t_philo) * (lf->num));
	if (!lf->philos)
		return (0);
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
 *	ms: 10^-3s	=> * 1000
 *	µs: 10^-6s	=> / 1000
 */
int	ft_gettime(void)
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