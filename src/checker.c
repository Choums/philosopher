/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:02:00 by root              #+#    #+#             */
/*   Updated: 2022/08/10 19:53:46 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
 *	Check les args. et init les structures.
*/

int	check_arg(int ac, char **av, t_life *lf)
{
	if (ac < 5 || ac > 6)
		return (0);
	lf->num = ft_atoi(av[1]);
	lf->t_die = ft_atoi(av[2]);
	lf->t_eat = ft_atoi(av[3]);
	lf->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		lf->n_eat = ft_atoi(av[5]);
	else
		lf->n_eat = -1;
	if (ac == 6 && ft_atoi(av[5]) == -1)
		return (0);
	lf->died = 0;
	if (!check_neg_arg(lf))
		return (0);
	pthread_mutex_init(&(lf->mem), NULL);
	pthread_mutex_init(&(lf->dis), NULL);
	return (1);
}

int	check_neg_arg(t_life *lf)
{
	if (lf->num <= 0)
		return (0);
	if (lf->t_die < 0 || lf->t_eat < 0 || lf->t_sleep < 0)
		return (0);
	if (lf->n_eat < -1)
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

int	ft_err(char *msg)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	return (1);
}
