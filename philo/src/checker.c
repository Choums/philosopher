/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:02:00 by root              #+#    #+#             */
/*   Updated: 2022/08/22 17:11:46 by chaidel          ###   ########.fr       */
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
	if (!strs_are_num(av))
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
	lf->stop = lf->num;
	if (lf->num <= 0)
		return (0);
	pthread_mutex_init(&(lf->starter), NULL);
	pthread_mutex_init(&(lf->dis), NULL);
	return (1);
}

int	strs_are_num(char **av)
{
	int	i;
	int	j;

	i = 1;
	if (!av)
		return (0);
	while (av[i])
	{
		j = 0;
		if (!av[i][j])
			return (0);
		while (av[i][j])
			if (!(av[i][j] >= '0' && av[i][j++] <= '9'))
				return (0);
		i++;
	}
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
